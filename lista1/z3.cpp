#include "z3.h"
#include <vector>
#include <iostream>


template<typename T, typename C>
T my_max(T a, T b, C comp) {
    return comp(a, b) ? b : a;
}

template<typename T>
void insertion_sort(std::vector<T>& vec) {
    for (int i = 1; i < vec.size(); ++i) {
        T key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

template<typename T, typename U>
T operator*(const cpplab::wektor<T>& v1, const std::vector<U>& v2) {
    T result = 0;
    for (int i = 0; i < v1.rozmiar(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

int main() {
    auto lambda = [](auto a, auto b) { return a < b; };
    std::cout << "my_max(10, 20): " << my_max(10, 20, lambda) << std::endl;
    std::cout << "my_max(3.14, 2.71): " << my_max(3.14, 2.71, lambda) << std::endl;
    std::cout << "my_max('a', 'b'): " << my_max('a', 'b', lambda) << std::endl;

    // z2
    std::vector<int> vec = { 9, 3, 5, 1, 7 };
    std::cout << "Wektor przed sortowaniem: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << "\n";

    insertion_sort(vec);

    std::cout << "Wektor po sortowaniu: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << "\n";

    // z3
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

    
    std::vector<int> vec2 = { 1, 2, 3 };
    int wynik_mnozenia = w * vec2;  // Mnożenie skalarne 
    std::cout << "Iloczyn skalarny " << wynik_mnozenia << std::endl;
}
