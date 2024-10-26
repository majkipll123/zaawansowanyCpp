#include <iostream>

// Funkcja bazowa dla przypadku, gdy nie ma już więcej argumentów
void print_all() {
    std::cout << std::endl;
}

// Szablon dla funkcji obsługującej dowolną liczbę argumentów
template<typename T, typename... Args>
void print_all(T first, Args... args) {
    std::cout << first << " ";      // Wypisanie pierwszego argumentu
    print_all(args...);             // Rekurencyjne wywołanie z pozostałymi argumentami
}

int main() {
    print_all(1, 1.0, 1.0f, "Hello");
    print_all(1, 2.0);
    print_all("Test", 42, 3.14, 'A');

    return 0;
}
