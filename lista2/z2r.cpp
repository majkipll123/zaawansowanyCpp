#include <iostream>

// Szablon ogólny klasy Factorial
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

// Specjalizacja dla N = 0, czyli przypadek bazowy: 0! = 1
template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main() {
    // Obliczenie silni dla liczby 5 w czasie kompilacji
    std::cout << "5! = " << Factorial<5>::value << std::endl;
    return 0;
}
