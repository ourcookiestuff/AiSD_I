/*Jakub Dziurka, 24.11.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make run
*/
#include <iostream>
#include <stdexcept>

// Interfejs kolejki dwustronnej
template <typename T>
class MyDeque {
private:
    T* data;            // Wskaźnik do tablicy dynamicznej przechowującej elementy
    int capacity;       // Pojemność tablicy (o jeden większa niż maksymalna liczba elementów)
    int frontIndex;      // Indeks początku kolejki
    int rearIndex;       // Indeks końca kolejki
    int currentSize;     // Aktualna liczba elementów w kolejce
    
public:
    // default constructor
    MyDeque(int capacity = 10) : capacity(capacity + 1), frontIndex(0), rearIndex(0), currentSize(0) {
        data = new T[this->capacity];
    }
    
    ~MyDeque() {
        delete[] data;
    }
    
    // copy constructor
    MyDeque(const MyDeque& other) : capacity(other.capacity), frontIndex(other.frontIndex), rearIndex(other.rearIndex), currentSize(other.currentSize) {
        data = new T[capacity];
        for (int i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // move constructor
    MyDeque(MyDeque&& other): data(other.data), capacity(other.capacity), frontIndex(other.frontIndex), rearIndex(other.rearIndex), currentSize(other.currentSize) {
        other.data = nullptr;
        other.capacity = 0;
        other.frontIndex = 0;
        other.rearIndex = 0;
        other.currentSize = 0;
    }
    
    // copy assignment operator, return *this
    MyDeque& operator=(const MyDeque& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            currentSize = other.currentSize;
            data = new T[capacity];
            for (int i = 0; i < capacity; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // move assignment operator, return *this
    MyDeque& operator=(MyDeque&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            frontIndex = other.frontIndex;
            rearIndex = other.rearIndex;
            currentSize = other.currentSize;
            other.data = nullptr;
            other.capacity = 0;
            other.frontIndex = 0;
            other.rearIndex = 0;
            other.currentSize = 0;
        }
        return *this;
    }
    
    // checks if the container has no elements
    bool empty() const {
        return currentSize == 0;
    }
    
    // liczba elementów w kolejce
    int size() const {
        return currentSize;
    }
    
    // dodanie na początek O(1)
    void push_front(const T& item) {
        if (currentSize == capacity - 1) {
            throw std::overflow_error("Deque jest pelne");
        }
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        data[frontIndex] = std::move(item);
        currentSize++;
    }
    
    // dodanie na początek O(1)
    void push_front(T&& item) {
        if (currentSize == capacity - 1) {
            throw std::overflow_error("Deque jest pelne");
        }
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        data[frontIndex] = std::move(item);
        currentSize++;
    }
    
    // dodanie na koniec O(1)
    void push_back(const T& item) {
        if (currentSize == capacity - 1) {
            throw std::overflow_error("Deque jest pelne");
        }
        data[rearIndex] = item;
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }
    
    // dodanie na koniec O(1)
    void push_back(T&& item) {
        if (currentSize == capacity - 1) {
            throw std::overflow_error("Deque jest pelne");
        }
        data[rearIndex] = item;
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }
    
    // zwraca początek, nie usuwa
    T& front() {
        if (empty()) {
            throw std::underflow_error("Deque jest puste");
        }
        return data[frontIndex];
    }
    
    // zwraca koniec, nie usuwa
    T& back() {
        if (empty()) {
            throw std::underflow_error("Deque jest puste");
        }
        return data[(rearIndex - 1 + capacity) % capacity];
    }
    
    // usuwa początek kolejki O(1)
    void pop_front() {
        if (empty()) {
            throw std::underflow_error("Deque jest puste");
        }
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
    }
    
    // usuwa koniec kolejki O(1)
    void pop_back() {
        if (empty()) {
            throw std::underflow_error("Deque jest puste");
        }
        rearIndex = (rearIndex - 1 + capacity) % capacity;
        currentSize--;
    }
    
    // czyszczenie listy z elementów
    void clear() {
        frontIndex = 0;
        rearIndex = 0;
        currentSize = 0;
    }
    
    void display()
    {
        int index = frontIndex;
        for (int i = 0; i < currentSize; ++i) {
            std::cout << data[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }
    
    // Operacje z indeksami.
    
    // Operator indeksowy
    T& operator[](int pos) {
        if (pos < 0 || pos >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[(frontIndex + pos) % capacity];
    }
    
    // Operator indeksowy dla stałego obiektu
    const T& operator[](int pos) const {
        if (pos < 0 || pos >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[(frontIndex + pos) % capacity];
    }
    
    // Usuwa element na podanej pozycji
    void erase(int pos) {
        if (pos < 0 || pos >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        
        int indexToRemove = (frontIndex + pos) % capacity;
        int indexToShift = (indexToRemove + 1) % capacity;
        
        for (int i = pos; i < currentSize - 1; ++i) {
            data[indexToRemove] = data[indexToShift];
            indexToRemove = indexToShift;
            indexToShift = (indexToShift + 1) % capacity;
        }
        
        rearIndex = (rearIndex - 1 + capacity) % capacity;
        currentSize--;
    }
    
    // Znajduje indeks podanego elementu
    int index(const T& item) {
        int idx = 0;
        for (int i = 0; i < currentSize; ++i) {
            if(data[(frontIndex + i) % capacity] == item) {
                return idx;
            }
            ++idx;
        }
        
        return -1;
    }
    
    // Wstawia element przed podaną pozycją
    void insert(int pos, const T& item) {
        if (pos < 0 || pos > currentSize) {
            throw std::out_of_range("Index out of range");
        }

        if (currentSize == capacity - 1) {
            throw std::overflow_error("Deque jest pelne");
        }

        int indexToInsert = (frontIndex + pos) % capacity;
        
        // Przesunięcie elementów w prawo
        for (int i = currentSize; i > pos; --i) {
            int indexToShift = (frontIndex + i - 1) % capacity;
            int nextIndex = (indexToShift + 1) % capacity;
            data[nextIndex] = std::move(data[indexToShift]);
        }

        // Wstawienie nowego elementu na odpowiednim miejscu
        data[indexToInsert] = item;
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }


    // Wstawia element przed podaną pozycją (wersja dla przenoszenia)
    void insert(int pos, T&& item) {
        if (pos < 0 || pos > currentSize) {
            throw std::out_of_range("Index out of range");
        }

        if (currentSize == capacity - 1) {
            throw std::overflow_error("Deque jest pelne");
        }

        int indexToInsert = (frontIndex + pos) % capacity;

        // Przesunięcie elementów w prawo
        for (int i = currentSize; i >= pos; --i) {
            int indexToShift = (frontIndex + i - 1) % capacity;
            int nextIndex = (indexToShift + 1) % capacity;
            data[nextIndex] = std::move(data[indexToShift]);
        }

        // Wstawienie nowego elementu na odpowiednim miejscu
        data[indexToInsert] = std::move(item);
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }

};

int main() {
    MyDeque<int> myDeque;

    // Test funkcji push_back i push_front
    myDeque.push_back(1);
    myDeque.push_back(2);
    myDeque.push_front(0);
    myDeque.push_back(3);

    // Oczekiwane wyniki: 0 1 2 3
    std::cout << "Deque after push_back and push_front: ";
    myDeque.display();

    // Test funkcji index
    int index0 = myDeque.index(0);
    int index1 = myDeque.index(1);
    int index2 = myDeque.index(2);
    int index3 = myDeque.index(3);

    std::cout << "Index of 0: " << index0 << std::endl;
    std::cout << "Index of 1: " << index1 << std::endl;
    std::cout << "Index of 2: " << index2 << std::endl;
    std::cout << "Index of 3: " << index3 << std::endl;

    
    // Test funkcji insert
    myDeque.insert(2, 10); // Wstawiamy 10 przed trzecim elementem

    // Oczekiwane wyniki: 0 1 10 2 3
    std::cout << "Deque after insert(2, 10): ";
    myDeque.display();

    // Test funkcji pop_front i pop_back
    myDeque.pop_front();
    myDeque.pop_back();

    // Oczekiwane wyniki: 1 10 2
    std::cout << "Deque after pop_front and pop_back: ";
    myDeque.display();

    // Test funkcji size
    int size = myDeque.size();

    // Oczekiwany wynik: 3
    std::cout << "Size of the deque: " << size << std::endl;

    // Test funkcji front i back
    int frontValue = myDeque.front();
    int backValue = myDeque.back();

    // Oczekiwane wyniki: Front: 1, Back: 2
    std::cout << "Front: " << frontValue << ", Back: " << backValue << std::endl;

    // Test funkcji clear
    std::cout << "Clear test" << std::endl;
    myDeque.clear();

    // Oczekiwany wynik: Lista jest pusta

    if (myDeque.empty()) {
        std::cout << "Deque jest puste" << std::endl;
    } else {
        std::cout << "Deque nie jest puste" << std::endl;
    }

    return 0;
}
