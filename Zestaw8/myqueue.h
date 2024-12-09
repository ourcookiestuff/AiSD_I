#ifndef QUEUE_MYQUEUE_H
#define QUEUE_MYQUEUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyQueue {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja

public:
    MyQueue(int s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyQueue() { delete [] tab; }
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue(MyQueue&& other); // move constructor
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    MyQueue& operator=(MyQueue&& other); // move assignment operator, return *this
    // UWAGA Po przeniesieniu other.msize = 1, other.head = other.tail = 0.
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize -1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize-1; }
    void push(const T& item); // dodanie na koniec
    void push(T&& item); // dodanie na koniec
    T& front() { return tab[head]; } // zwraca początek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop(); // usuwa początek
    void clear(); // czyszczenie listy z elementów
    void display();
};

template <typename T>
MyQueue<T>::MyQueue(const MyQueue& other) : msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    assert(tab != nullptr);

    for (int i = 0; i < msize; ++i) {
        tab[i] = other.tab[i];
    }
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue&& other) : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail) {
    other.tab = nullptr;
    other.msize = 1;
    other.head = other.tail = 0;
}

template <typename T>
MyQueue<T>&  MyQueue<T>::operator=(const MyQueue& other) {
    if (this != &other) {
        delete[] tab;

        msize = other.msize;
        head = other.head;
        tail = other.tail;

        tab = new T[msize];
        assert(tab != nullptr);

        for (int i = 0; i < msize; ++i) {
            tab[i] = other.tab[i];
        }
    }
    return *this;
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other) {
    if (this != &other) {
        delete[] tab;

        tab = other.tab;
        msize = other.msize;
        head = other.head;
        tail = other.tail;

        other.tab = nullptr;
        other.msize = 1;
        other.head = other.tail = 0;
    }
    return *this;
}

template <typename T>
void MyQueue<T>::push(const T& item) {
    if (!full()) {
        tab[tail] = item;
        tail = (tail + 1) % msize;
    } else {
        std::cerr << "Kolejka jest pełna\n";
    }
}

template <typename T>
void MyQueue<T>::push(T&& item) {
    if (!full()) {
        tab[tail] = std::move(item);
        tail = (tail + 1) % msize;
    } else {
        std::cerr << "Kolejka jest pełna\n";
    }
}

template <typename T>
void MyQueue<T>::pop() {
    if(!empty()) {
        head = (head + 1) % msize;
    } else {
        std::cerr << "Kolejka jest pusta\n";
    }
}

template <typename T>
void MyQueue<T>::clear() {
    head = tail = 0;
}

template <typename T>
void MyQueue<T>::display() {
    int current = head;
    while (current != tail) {
        std::cout << tab[current] << " ";
        current = (current + 1) % msize;
    }
    std::cout << std::endl;
}

#endif
