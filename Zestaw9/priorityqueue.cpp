/*Jakub Dziurka, 12.12.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make run
*/
#include <iostream>
#include "priorityqueue.h"

int main() {
    MyPriorityQueue<int> myQueue;

    // Testowanie dodawania elementów
    myQueue.push(3);
    myQueue.push(1);
    myQueue.push(4);
    myQueue.push(1);
    myQueue.push(5);

    std::cout << "Initial queue: ";
    myQueue.display(); // Wyświetlanie kolejki

    // Testowanie odczytu największego elementu
    std::cout << "Top element: " << myQueue.top() << std::endl;

    // Testowanie usuwania elementu największego
    myQueue.pop();
    std::cout << "Queue after pop: ";
    myQueue.display();

    // Testowanie czyszczenia kolejki
    myQueue.clear();
    std::cout << "Queue after clear: ";
    myQueue.display();

    // Testowanie przenoszenia
    MyPriorityQueue<int> anotherQueue;
    anotherQueue.push(8);
    anotherQueue.push(2);
    anotherQueue.push(7);

    std::cout << "Another queue before move: ";
    anotherQueue.display();

    myQueue = std::move(anotherQueue);

    std::cout << "My queue after move: ";
    myQueue.display();

    return 0;
}

