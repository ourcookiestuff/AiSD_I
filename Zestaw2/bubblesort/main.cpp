/*Jakub Dziurka, 17.10.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make
    ./bubblesort
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

template <typename T> void bubbleSort(T &arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; i++) {
    // Iteracja po elementach od początku do n-i-1, gdzie i to obecny przebieg sortowania
    for (int j = 0; j < n - i - 1; j++) {
      // Porównujemy sąsiednie elementy
      if (arr[j] > arr[j + 1]) {
        // Jeśli element na pozycji j jest większy od elementu na pozycji j+1, zamieniamy je miejscami
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <typename T> bool isSorted(const T &arr) {
  for (size_t i = 1; i < arr.size(); i++) {
    if (arr[i] < arr[i - 1]) {
      return false; // Jeśli znaleziono element w złej kolejności, zwracamy false
    }
  }
  return true; // Jeśli nie znaleziono żadnych błędów, zwracamy true
}

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr))); // Inicjalizacja generatora liczb losowych
  std::vector<int> arr;

  // Wypełnienie wektora losowymi liczbami
  for (int i = 0; i < 10; i++) {      // Losujemy 10 liczb
    arr.push_back(std::rand() % 100); // Zakres od 0 do 99
  }

  std::cout << "Nieposortowane wartości: ";
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  bubbleSort(arr);

  std::cout << "Posortowane wartości: ";
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  if (isSorted(arr)) {
    std::cout << "Macierz jest posortowana." << std::endl;
  } else {
    std::cout << "Macierz nie jest posortowana." << std::endl;
  }

  return 0;
}
