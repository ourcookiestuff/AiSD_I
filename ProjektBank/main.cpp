#include <iostream>
#include <sqlite3.h>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>

class BankAccount {
public:
    BankAccount(std::string accountNumber, std::string owner, double balance, std::string password)
            : accountNumber(accountNumber), owner(owner), balance(balance), password(password) {}

    std::string getAccountNumber() const { return accountNumber; }
    std::string getOwner() const { return owner; }
    double getBalance() const { return balance; }
    std::string getPassword() const { return password; }

private:
    std::string accountNumber;
    std::string owner;
    double balance;
    std::string password;
};

class BankDatabase {
public:
    BankDatabase(const char* dbPath) {
        sqlite3_open(dbPath, &db);
        char* errorMessage;
        const char* sqlCreateTable =
                "CREATE TABLE IF NOT EXISTS accounts ("
                "accountNumber TEXT PRIMARY KEY, "
                "owner TEXT NOT NULL, "
                "balance REAL NOT NULL, "
                "password TEXT NOT NULL);";

        if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
            std::cerr << "Błąd SQLite: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
        }
    }

    ~BankDatabase() {
        sqlite3_close(db);
    }

    bool validateAccountPassword(const std::string& accountNumber, const std::string& inputPassword) {
        std::string sqlQuery = "SELECT password FROM accounts WHERE accountNumber = '" + accountNumber + "';";
        std::string storedPassword;
        bool valid = false;

        executeSqlQuery(sqlQuery, [&storedPassword, &valid](sqlite3_stmt* stmt) {
            storedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            valid = true;
        });

        if (!valid) {
            return false;
        }

        return storedPassword == inputPassword;
    }

    void addAccount(const BankAccount& account) {
        if (accountExists(account.getAccountNumber())) {
            std::cerr << "Błąd: Konto o numerze " << account.getAccountNumber() << " już istnieje." << std::endl;
            return;
        }

        std::string sqlInsert = "INSERT INTO accounts (accountNumber, owner, balance, password) VALUES ('"
                                + account.getAccountNumber() + "', '"
                                + account.getOwner() + "', "
                                + std::to_string(account.getBalance()) + ", '"
                                + account.getPassword() + "');";
        executeSql(sqlInsert);
    }

    bool accountExists(const std::string& accountNumber) {
        bool exists = false;
        std::string sqlQuery = "SELECT count(*) FROM accounts WHERE accountNumber = '" + accountNumber + "';";
        executeSqlQuery(sqlQuery, [&exists](sqlite3_stmt* stmt) {
            exists = sqlite3_column_int(stmt, 0) > 0;
        });
        return exists;
    }

    void deleteAccount(const std::string& accountNumber) {
        std::string sqlDelete = "DELETE FROM accounts WHERE accountNumber = '" + accountNumber + "';";
        executeSql(sqlDelete);
    }

    bool withdraw(const std::string& accountNumber, double amount) {
        if (!accountExists(accountNumber)) {
            std::cerr << "Błąd: Konto o numerze " << accountNumber << " nie istnieje." << std::endl;
            return false;
        }

        double balance = getBalance(accountNumber);

        if (amount > balance) {
            std::cerr << "Niewystarczające środki na koncie." << std::endl;
            return false;
        }
        return updateBalance(accountNumber, balance - amount);
    }

    bool deposit(const std::string& accountNumber, double amount) {
        if (!accountExists(accountNumber)) {
            std::cerr << "Błąd: Konto o numerze " << accountNumber << " nie istnieje." << std::endl;
            return false;
        }

        double balance = getBalance(accountNumber);
        return updateBalance(accountNumber, balance + amount);
    }

    bool transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
        if (!accountExists(fromAccount)) {
            std::cerr << "Błąd: Konto źródłowe o numerze " << fromAccount << " nie istnieje." << std::endl;
            return false;
        }
        if (!accountExists(toAccount)) {
            std::cerr << "Błąd: Konto docelowe o numerze " << toAccount << " nie istnieje." << std::endl;
            return false;
        }
        if (!withdraw(fromAccount, amount)) {
            return false;
        }
        return deposit(toAccount, amount);
    }

    double getBalance(const std::string& accountNumber) {
        std::string sqlQuery = "SELECT balance FROM accounts WHERE accountNumber = '" + accountNumber + "';";
        double balance = 0.0;
        executeSqlQuery(sqlQuery, [&balance](sqlite3_stmt* stmt) {
            balance = sqlite3_column_double(stmt, 0);
        });
        return balance;
    }

    void printAllAccounts() {
        std::string sqlQuery = "SELECT accountNumber, owner, balance, password FROM accounts;";
        executeSqlQuery(sqlQuery, [](sqlite3_stmt* stmt) {
            std::string accountNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string owner = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            double balance = sqlite3_column_double(stmt, 2);
            std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

            std::cout << "Numer konta: " << accountNumber
            << ", Właściciel: " << owner
            << ", Saldo: " << balance
            << ", Hasło: " << password << std::endl;
        });
    }

private:
    bool updateBalance(const std::string& accountNumber, double newBalance) {
        std::string sqlUpdate = "UPDATE accounts SET balance = " + std::to_string(newBalance)
                                + " WHERE accountNumber = '" + accountNumber + "';";
        return executeSql(sqlUpdate);
    }

    bool executeSql(const std::string& sql) {
        char* errorMessage;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
            std::cerr << "Błąd SQLite: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
            return false;
        }
        return true;
    }

    void executeSqlQuery(const std::string& sql, std::function<void(sqlite3_stmt*)> callback) {
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Błąd SQLite w przygotowaniu zapytania: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            callback(stmt);
        }

        sqlite3_finalize(stmt);
    }

    sqlite3* db;
};

bool backupDatabase(const std::string& dbPath, const std::string& backupPath) {
    std::ifstream src(dbPath, std::ios::binary);
    std::ofstream dst(backupPath, std::ios::binary);

    if (!src || !dst) {
        return false;
    }

    dst << src.rdbuf();
    return true;
}

bool restoreDatabase(const std::string& backupPath, const std::string& dbPath) {
    std::ifstream src(backupPath, std::ios::binary);
    std::ofstream dst(dbPath, std::ios::binary);

    if (!src || !dst) {
        return false;
    }

    dst << src.rdbuf();
    return true;
}

void showMenu() {
    std::cout << "1. Otwórz nowe konto" << std::endl;
    std::cout << "2. Usuń konto" << std::endl;
    std::cout << "3. Wpłać środki" << std::endl;
    std::cout << "4. Wypłać środki" << std::endl;
    std::cout << "5. Przelej środki" << std::endl;
    std::cout << "6. Pokaż saldo" << std::endl;
    std::cout << "7. Utwórz kopię zapasową bazy danych" << std::endl;
    std::cout << "8. Przywróć bazę danych z kopii zapasowej" << std::endl;
    std::cout << "9. Wypisz dane z bazy" << std::endl;
    std::cout << "0. Wyjście" << std::endl;
    std::cout << "Wybierz opcję: ";
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

std::string getPassword() {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    std::cin >> password;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << "\n";
    return password;
}

int main() {
    BankDatabase db("bank.db");
    int choice;
    std::string accountNumber, toAccountNumber, owner, backupPath, password, fromPassword;
    double amount;

    clearScreen();
    while (true) {
        showMenu();
        std::cin >> choice;

        clearScreen();
        switch (choice) {
            case 1: // Otwórz nowe konto
                std::cout << "Numer konta: ";
                std::cin >> accountNumber;
                std::cout << "Właściciel: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoruj pozostałe znaki nowej linii w buforze
                std::getline(std::cin, owner);
                std::cout << "Hasło: ";
                password = getPassword();
                db.addAccount(BankAccount(accountNumber, owner, 0.0, password));
                break;
            case 2: // Usuń konto
                std::cout << "Numer konta do usunięcia: ";
                std::cin >> accountNumber;
                std::cout << "Hasło: ";
                password = getPassword();
                if (db.validateAccountPassword(accountNumber, password)) {
                    std::cout << "Konto usuniete" << std::endl;
                    db.deleteAccount(accountNumber);
                } else {
                    std::cout << "Nieudana operacja: nieprawidłowe hasło." << std::endl;
                }
                break;
            case 3: // Wpłać środki
                std::cout << "Numer konta: ";
                std::cin >> accountNumber;
                std::cout << "Kwota: ";
                std::cin >> amount;
                db.deposit(accountNumber, amount);
                break;
            case 4: // Wypłać środki
                std::cout << "Numer konta: ";
                std::cin >> accountNumber;
                std::cout << "Kwota: ";
                std::cin >> amount;
                std::cout << "Hasło: ";
                password = getPassword();
                if (db.validateAccountPassword(accountNumber, password) && db.withdraw(accountNumber, amount)) {
                    std::cout << "Wypłata wykonana pomyślnie." << std::endl;
                } else {
                    std::cout << "Nieudana operacja wypłaty." << std::endl;
                }
                break;
            case 5: // Przelej środki
                std::cout << "Z konta: ";
                std::cin >> accountNumber;
                std::cout << "Hasło konta źródłowego: ";
                fromPassword = getPassword();
                std::cout << "Na konto: ";
                std::cin >> toAccountNumber;
                std::cout << "Kwota: ";
                std::cin >> amount;
                if (db.validateAccountPassword(accountNumber, fromPassword)) {
                    if (!db.transfer(accountNumber, toAccountNumber, amount)) {
                        std::cout << "Nieudana operacja przelewu." << std::endl;
                    } else {
                        std::cout << "Przelew wykonany pomyślnie." << std::endl;
                    }
                } else {
                    std::cout << "Nieudana operacja: nieprawidłowe hasło." << std::endl;
                }
                break;
            case 6: // Pokaż saldo
                std::cout << "Numer konta: ";
                std::cin >> accountNumber;
                std::cout << "Hasło: ";
                password = getPassword();
                if (!db.accountExists(accountNumber)) {
                    std::cerr << "Błąd: Konto o numerze " << accountNumber << " nie istnieje." << std::endl;
                }
                else if (db.validateAccountPassword(accountNumber, password)) {
                    double balance = db.getBalance(accountNumber);
                    std::cout << "Saldo: " << balance << std::endl;
                } else {
                    std::cout << "Nieudana operacja: nieprawidłowe hasło." << std::endl;
                }
                break;
            case 7: // Utwórz kopię zapasową
                std::cout << "Podaj ścieżkę do pliku kopii zapasowej: ";
                std::cin >> backupPath;
                if (backupDatabase("bank.db", backupPath)) {
                    std::cout << "Kopia zapasowa utworzona pomyślnie." << std::endl;
                } else {
                    std::cout << "Błąd podczas tworzenia kopii zapasowej." << std::endl;
                }
                break;
            case 8: // Przywróć bazę danych z kopii
                std::cout << "Podaj ścieżkę do pliku kopii zapasowej: ";
                std::cin >> backupPath;
                if (restoreDatabase(backupPath, "bank.db")) {
                    std::cout << "Baza danych przywrócona pomyślnie." << std::endl;
                } else {
                    std::cout << "Błąd podczas przywracania bazy danych." << std::endl;
                }
                break;
            case 9: // Wypisywanie wartości z bazy danych
                db.printAllAccounts();
                break;
            case 0: // Wyjście
                return 0;
            default:
                std::cout << "Nieznana opcja." << std::endl;
        }

    }
}
