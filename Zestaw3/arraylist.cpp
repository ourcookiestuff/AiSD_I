/*Jakub Dziurka, 24.10.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make
    ./arraylist.out
*/
#include <iostream>
#include "arraylist.h"

int main() {
    ArrayList<int> list(5);

    // Test funkcji push_back
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    std::cout << "push_back Test: " << list << std::endl;

    // Test funkcji reverse
    list.reverse();
    std::cout << "Reverse Test: " << list << std::endl;

    // Test funkcji sort
    list.sort();
    std::cout << "Sort Test: " << list << std::endl;

    // Test funkcji merge
    ArrayList<int> other(3);
    other.push_back(0);
    other.push_back(6);
    other.push_back(7);
    list.merge(other);
    std::cout << "Merge Test: " << list << std::endl;

    // Test funkcji push_front
    list.push_front(8);
    std::cout << "push_front Test: " << list << std::endl;

    // Test funkcji pop_front
    list.pop_front();
    std::cout << "pop_front Test: " << list << std::endl;

    // Test funkcji pop_back
    list.pop_back();
    std::cout << "pop_back Test: " << list << std::endl;

    // Test funkcji clear
    list.clear();
    std::cout << "Clear Test: " << list << std::endl;

    // Test funkcji operator[]
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    std::cout << "Operator[] Test: list[1] = " << list[1] << std::endl;

    // Test funkcji index
    int index = list.index(2);
    std::cout << "Index Test: Index of 2 = " << index << std::endl;

    // Test funkcji insert
    list.insert(1, 4);
    std::cout << "Insert Test: " << list << std::endl;

    // Test funkcji erase
    list.erase(1);
    std::cout << "Erase Test: " << list << std::endl;

    return 0;
}
