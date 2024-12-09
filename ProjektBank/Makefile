# Nazwa pliku wykonywalnego
TARGET = bank_system

# Kompilator
CC = g++

# Opcje kompilatora
CFLAGS = -Wall -std=c++11

# Ścieżka do bibliotek
LDFLAGS = -lsqlite3

# Plik(i) źródłowe
SRC = main.cpp

# Polecenie domyślne
all: $(TARGET)

# Reguła linkowania
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Uruchamianie programu
.PHONY: run
run:
	./$(TARGET)

# Czyszczenie projektu (usuwanie plików wykonywalnych i obiektowych)
.PHONY: clean
clean:
	rm -f $(TARGET)
