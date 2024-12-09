/*Jakub Dziurka, 17.10.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make
    ./quicksort
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

template <typename T> void quicksort(T &arr, int lewo, int prawo) {
  // Wybieramy element środkowy jako pivot
  auto pivot = arr[(lewo + prawo) / 2];
  int i = lewo;
  int j = prawo;

  while (i <= j) {
    // Przesuwamy wskaźnik i w prawo, dopóki wartość na pozycji i jest mniejsza od pivot
    while (arr[i] < pivot) {
      i++;
    }
    // Przesuwamy wskaźnik j w lewo, dopóki wartość na pozycji j jest większa od pivot
    while (arr[j] > pivot) {
      j--;
    }
    // Jeśli i <= j, to zamieniamy elementy na pozycjach i i j ze sobą
    if (i <= j) {
      std::swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }

  // Rekurencyjnie sortujemy lewą stronę (elementy mniejsze od pivot)
  if (lewo < j) {
    quicksort(arr, lewo, j);
  }
  // Rekurencyjnie sortujemy prawą stronę (elementy większe od pivot)
  if (i < prawo) {
    quicksort(arr, i, prawo);
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

  quicksort(arr, 0, arr.size() - 1);

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
