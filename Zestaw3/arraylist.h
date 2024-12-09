// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; } // destruktor

    ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) // copy constructor
    {
        tab = new T[msize];
        for (int i = 0; i < last; ++i) {
            tab[i] = other.tab[i];
        }
    }
    // usage:   ArrayList<int> list2(list1);

    ArrayList(ArrayList&& other) : tab(other.tab), msize(other.msize), last(other.last) // move constructor NIEOBOWIAZKOWE
    {
        other.tab = nullptr;
        other.msize = 0;
        other.last = 0;
    }
    // usage:   ArrayList<int> list2(std::move(list1));

    ArrayList& operator=(const ArrayList& other) // copy assignment operator, return *this
    {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            last = other.last;
            tab = new T[msize];
            for (int i = 0; i < last; ++i) {
                tab[i] = other.tab[i];
            }
        }
        return *this;
    }
    // usage:   list2 = list1;

    ArrayList& operator=(ArrayList&& other) // move assignment operator, return *this
    {
        if (this != &other) {
            delete[] tab;
            tab = other.tab;
            msize = other.msize;
            last = other.last;
            other.tab = nullptr;
            other.msize = 0;
            other.last = 0;
        }
        return *this;
    }
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push_front(const T& item) // dodanie na poczatek
    {
        if(full()){
            std::cout << "Error: Lista jest pelna" << std::endl;
        }
        else {
            for (int i = last; i > 0; --i) {
                tab[i] = tab[i - 1];
            }
            tab[0] = item;
            last++;
        }
    }
    void push_front(T&& item) // dodanie na poczatek NIEOBOWIAZKOWE
    {
        if(full()){
            std::cout << "Error: Lista jest pelna" << std::endl;
        }
        else {
            for (int i = last; i > 0; --i) {
                tab[i] = tab[i - 1];
            }
            tab[0] = item;
            last++;
        }
    }
    void push_back(const T& item) // dodanie na koniec
    {
        if(full()){
            std::cout << "Error: Lista jest pelna" << std::endl;
        }
        else{
            tab[last] = item;
            last++;
        }
    }
    void push_back(T&& item) // dodanie na koniec NIEOBOWIAZKOWE
    {
        if(full()){
            std::cout << "Error: Lista jest pelna" << std::endl;
        }
        else{
            tab[last] = item;
            last++;
        }
    }
    T& front() // zwraca poczatek, nie usuwa, error dla pustej listy
    {
        if(empty()){
            std::cout << "Error: Lista jest pusta" << std::endl;
        }

        return  tab[0];
    }
    T& back() // zwraca koniec, nie usuwa, error dla pustej listy
    {
        if(last == 0){
            std::cout << "Error: Lista jest pusta" << std::endl;
        }

        return tab[last-1];
    }
    void pop_front() // usuwa poczatek, error dla pustej listy
    {
        if(empty()){
            std::cout << "Error: Lista jest pusta" << std::endl;
        }
        else{
            int i;
            for(i = 0; i < last - 1; i++){
                tab[i] = tab[i+1];
            }
            last--;
        }
    }
    void pop_back() // usuwa koniec, error dla pustej listy
    {
        if(empty()){
            std::cout << "Error: Lista jest pusta" << std::endl;
        }
        else{
            last--;
        }
    }
    void clear() // czyszczenie listy z elementow
    {
        for(int i = 0; i < last; i++){
            tab[i] = 0;
        }
        last = 0;
    }
    void display() // lepiej zdefiniowac operator<<
    {
        for(int i = 0; i < last; i++){
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    }
    void reverse() // odwracanie kolejnosci
    {
        int left = 0;
        int right = last - 1;

        while(left < right){
            std::swap(tab[left], tab[right]);
            left++;
            right--;
        }
    }
    void sort() // sortowanie listy
    {
        int index = 0;
        for(int i = 0; i < size(); i++)
        {
            index = 0;
            for(int j = 0; j < size() - i; j++)
            {
                if(tab[j] > tab[index])
                {
                    index = j;
                }
            }
            T temp = tab[last - i - 1];
            tab[last - i - 1] = tab[index];
            tab[index] = temp;
        }
    }
    void merge(ArrayList& other) //  merges two sorted lists into one NIEOBOWIAZKOWE
    {
        ArrayList<T> result(max_size() + other.max_size());

        int i = 0, j = 0;
        while (i < last && j < other.size()) {
            if (tab[i] < other.tab[j]) {
                result.push_back(tab[i]);
                i++;
            } else {
                result.push_back(other.tab[j]);
                j++;
            }
        }

        while (i < last) {
            result.push_back(tab[i]);
            i++;
        }

        while (j < other.size()) {
            result.push_back(other.tab[j]);
            j++;
        }

        *this = std::move(result);
    }

    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](int pos) // podstawienie L[pos]=item, odczyt L[pos]
    {
        if(pos >= last)
        {
            std::cout << "Index poza tablica!" << std::endl;
        }
        return tab[pos];
    }
    const T& operator[](int pos) const // dostep do obiektu const
    {
        if(pos >= last)
        {
            std::cout << "Index poza tablica!" << std::endl;
        }
        return tab[pos];
    }
    void erase(int pos) // usuniecie elementu na pozycji pos
    {
        if (pos < 0 || pos >= last) {
            std::cout << "Error: Nieprawidlowa pozycja kasowania" << std::endl;
        }

        for (int i = pos; i < last - 1; i++) {
            tab[i] = tab[i + 1];
        }

        last--;
    }
    int index(const T& item) // jaki index na liscie (-1 gdy nie ma)
    {
        for (int i = 0; i < last; i++) {
            if (tab[i] == item) {
                return i;
            }
        }

        return -1;  // Nie znaleziono
    }
    void insert(int pos, const T& item) // inserts item before pos
    {
        if (pos < 0 || pos > last) {
            std::cout << "Error: Nieprawidlowa pozycja do wstawienia" << std::endl;
        }

        if (full()) {
            std::cout << "Error: Lista jest pelna" << std::endl;
        }

        for (int i = last; i > pos; i--) {
            tab[i] = tab[i - 1];
        }

        tab[pos] = item;
        last++;
    }
    void insert(int pos, T&& item) // inserts item before pos
    {
        assert(pos >= 0 && pos <= last); // Sprawdzamy, czy pozycja jest w zakresie.

        if (full()) {
            std::cerr << "Lista jest pełna. Nie można wstawić nowego elementu." << std::endl;
        }

        for (int i = last; i > pos; --i) {
            tab[i] = std::move(tab[i - 1]);
        }

        tab[pos] = std::move(item);

        last++;
    }
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
