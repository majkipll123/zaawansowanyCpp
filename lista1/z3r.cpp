#include "z3.h"
#include <vector>      // std::vector
#include <iostream>    // std::cout
#include <functional>  // std::function

// Zadanie 1: Szablon funkcji my_max
template<typename T, typename C>
T my_max(T a, T b, C comp) {
    return comp(a, b) ? b : a;
}

// Zadanie 2: Szablon funkcji insertion_sort
template<typename T>
void insertion_sort(std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); i++) {
        T key = vec[i];
        int j = i - 1;

        // Porównujemy elementy i przesuwamy je w prawo
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
}

// Zadanie 3c: Operator mnożenia skalarnego
template<typename T, typename U>
T operator*(const cpplab::wektor<T>& v1, const std::vector<U>& v2) {
    T result = 0;
    size_t min_size = std::min(v1.rozmiar(), static_cast<int>(v2.size()));
    
    for (size_t i = 0; i < min_size; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

template<typename T, typename U>
T operator*(const std::vector<U>& v2, const cpplab::wektor<T>& v1) {
    return v1 * v2; // wywołanie operatora w odwrotnej kolejności
}

int main() {
    // Test dla Zadania 1: my_max
    auto lambda = [](auto a, auto b) { return a < b; };
    std::cout << "my_max(10, 20): " << my_max(10, 20, lambda) << std::endl;
    std::cout << "my_max(3.14, 2.71): " << my_max(3.14, 2.71, lambda) << std::endl;
    std::cout << "my_max('a', 'b'): " << my_max('a', 'b', lambda) << std::endl;

    // Test dla Zadania 2: insertion_sort
    std::vector<int> vec = { 9, 3, 5, 1, 7 };
    std::cout << "Wektor przed sortowaniem: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;

    insertion_sort(vec);

    std::cout << "Wektor po sortowaniu: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << std::endl;

    // Test dla Zadania 3: cpplab::wektor
    cpplab::wektor<int> w;
    w.dodaj(10);
    w.dodaj(20);
    w.dodaj(30);

    std::cout << "Wektor po dodaniu elementów: ";
    w.wypisz();

    std::cout << "Rozmiar wektora: " << w.rozmiar() << std::endl;
    std::cout << "Pojemność wektora: " << w.zdobadz_pojemnosc() << std::endl;

    w[1] = 100; // Zmiana elementu
    std::cout << "Wektor po zmianie elementu: ";
    w.wypisz();

    // Test operatora mnożenia skalarnego
    std::vector<int> vec2 = { 1, 2, 3 };
    int wynik_mnozenia = w * vec2;  // Mnożenie skalarne
    std::cout << "Iloczyn skalarny cpplab::wektor i std::vector: " << wynik_mnozenia << std::endl;

    return 0;
}
