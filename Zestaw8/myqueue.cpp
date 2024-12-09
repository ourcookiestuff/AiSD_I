#include <iostream>
#include "myqueue.h"

int main() {
    MyQueue<int> myQueue;

    // Test funkcji push
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(0);
    myQueue.push(3);

    // Oczekiwane wyniki: 1 2 0 3
    std::cout << "Queue after push: ";
    myQueue.display();

    // Test funkcji pop
    myQueue.pop();

    // Oczekiwane wyniki: 1 10 2
    std::cout << "Queue after pop: ";
    myQueue.display();

    // Test funkcji size
    int size = myQueue.size();

    // Oczekiwany wynik: 3
    std::cout << "Size of the queue: " << size << std::endl;

    // Test funkcji max_size
    int max_size = myQueue.max_size();

    // Oczekiwany wynik: 10
    std::cout << "Max size of the queue: " << max_size << std::endl;

    // Test funkcji front i back
    int frontValue = myQueue.front();
    int backValue = myQueue.back();

    // Oczekiwane wyniki: Front: 2, Back: 3
    std::cout << "Front: " << frontValue << ", Back: " << backValue << std::endl;

    // Test funkcji clear
    std::cout << "Clear test" << std::endl;
    myQueue.clear();

    // Oczekiwany wynik: Kolejka jest pusta

    if (myQueue.empty()) {
        std::cout << "Kolejka jest pusta" << std::endl;
    } else {
        std::cout << "Kolejka nie jest pusta" << std::endl;
    }

    return 0;
}