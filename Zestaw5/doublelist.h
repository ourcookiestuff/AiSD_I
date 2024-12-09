// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const; // dostep do obiektu const
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

// Destruktor
template <typename T>
DoubleList<T>::~DoubleList() {
    clear();
}

// Konstruktor kopiujący
template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) {
    head = tail = nullptr;
    DoubleNode<T>* temp = other.head;

    while (temp != nullptr) {
        push_back(temp->value);
        temp = temp->next;
    }
}

// Konstruktor przenoszący
template <typename T>
DoubleList<T>::DoubleList(DoubleList&& other) {
    head = other.head;
    tail = other.tail;
    other.head = other.tail = nullptr;
}

// Operator przypisania kopiującego
template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) {
        clear();

        DoubleNode<T>* temp = other.head;

        while (temp != nullptr) {
            push_back(temp->value);
            temp = temp->next;
        }
    }
    return *this;
}

// Operator przypisania przenoszącego
template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& other) {
    if (this != &other) {
        clear();

        head = other.head;
        tail = other.tail;
        other.head = other.tail = nullptr;
    }
    return *this;
}

// Zwraca rozmiar listy
template <typename T>
int DoubleList<T>::size() const {
    int count = 0;
    DoubleNode<T>* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

// Dodaje element na koniec listy
template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(item, nullptr, tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(std::move(item), nullptr, tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

// Usuwa pierwszy element z listy
template <typename T>
void DoubleList<T>::pop_front() {
    if (!empty()) {
        DoubleNode<T>* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        delete temp;
    }
}

// Usuwa ostatni element z listy
template <typename T>
void DoubleList<T>::pop_back() {
    if (!empty()) {
        DoubleNode<T>* temp = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete temp;
    }
}

// Czyści listę z elementów
template <typename T>
void DoubleList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

// Wyświetla listę
template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T>* current = head;

    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }

    std::cout << std::endl;
}

// Wyświetla listę odwróconą
template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T>* current = tail;

    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->prev;
    }

    std::cout << std::endl;
}

template <typename T>
T& DoubleList<T>::operator[](int pos) {
    if (pos < 0 || pos >= size()) {
        // Obsługa błędnej pozycji
        throw std::out_of_range("Invalid index");
    }

    DoubleNode<T>* current = head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }

    return current->value;
}

template <typename T>
const T& DoubleList<T>::operator[](int pos) const {
    if (pos < 0 || pos >= size()) {
        // Obsługa błędnej pozycji
        throw std::out_of_range("Invalid index");
    }

    DoubleNode<T>* current = head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }

    return current->value;
}

template <typename T>
void DoubleList<T>::erase(int pos) {
    if (pos < 0 || pos >= size()) {
        // Obsługa błędnej pozycji
        throw std::out_of_range("Invalid index");
    }

    DoubleNode<T>* current = head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }

    if (current == head) {
        pop_front();
    } else if (current == tail) {
        pop_back();
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}

template <typename T>
int DoubleList<T>::index(const T& item) {
    int idx = 0;
    DoubleNode<T>* current = head;

    while (current != nullptr) {
        if (current->value == item) {
            return idx;
        }
        current = current->next;
        ++idx;
    }

    return -1; // Element nie znaleziony
}

template <typename T>
void DoubleList<T>::insert(int pos, const T& item) {
    if (pos < 0 || pos > size()) {
        // Obsługa błędnej pozycji
        throw std::out_of_range("Invalid index");
    }

    if (pos == 0) {
        push_front(item);
    } else if (pos == size()) {
        push_back(item);
    } else {
        DoubleNode<T>* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }

        current->next = new DoubleNode<T>(item, current->next, current);
        current->next->next->prev = current->next;
    }
}

template <typename T>
void DoubleList<T>::insert(int pos, T&& item) {
    if (pos < 0 || pos > size()) {
        // Obsługa błędnej pozycji
        throw std::out_of_range("Invalid index");
    }

    if (pos == 0) {
        push_front(std::move(item));
    } else if (pos == size()) {
        push_back(std::move(item));
    } else {
        DoubleNode<T>* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }

        current->next = new DoubleNode<T>(std::move(item), current->next, current);
        current->next->next->prev = current->next;
    }
}

#endif

// EOF
