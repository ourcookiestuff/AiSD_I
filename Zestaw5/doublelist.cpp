#include <iostream>
#include "doublelist.h"

int main() {
    DoubleList<int> list;

    // Test funkcji push_back i push_front
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    list.push_back(3);

    // Oczekiwane wyniki: 0 1 2 3
    std::cout << "List after push_back and push_front: ";
    list.display();

    // Test funkcji index
    int index1 = list.index(2); // Oczekiwany wynik: 2 (indeks drugiego elementu)
    int index2 = list.index(5); // Oczekiwany wynik: -1 (element nie istnieje)

    std::cout << "Index of 2: " << index1 << std::endl;
    std::cout << "Index of 5: " << index2 << std::endl;

    // Test funkcji insert
    list.insert(2, 10); // Wstawiamy 10 przed trzecim elementem

    // Oczekiwane wyniki: 0 1 10 2 3
    std::cout << "List after insert(2, 10): ";
    list.display();

    // Test funkcji reverse
    // Oczekiwany wynik: 3 2 10 1 0
    std::cout << "List after reverse: ";
    list.display_reversed();

    // Test funkcji pop_front i pop_back
    list.pop_front();
    list.pop_back();

    // Oczekiwane wyniki: 1 10 2
    std::cout << "List after pop_front and pop_back: ";
    list.display();

    // Test funkcji size
    int size = list.size();

    // Oczekiwany wynik: 3
    std::cout << "Size of the list: " << size << std::endl;

    // Test funkcji front i back
    int frontValue = list.front();
    int backValue = list.back();

    // Oczekiwane wyniki: Front: 1, Back: 2
    std::cout << "Front: " << frontValue << ", Back: " << backValue << std::endl;

    // Test funkcji clear
    list.clear();

    // Oczekiwany wynik: Lista jest pusta

    if (list.empty()) {
        std::cout << "Lista jest pusta" << std::endl;
    } else {
        std::cout << "Lista nie jest pusta" << std::endl;
    }

    return 0;
}
