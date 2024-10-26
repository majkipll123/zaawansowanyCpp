#include <iostream>

template<typename... Args>
void print_all(Args... args) {
    // Fold expression używa operatora "<<" i składni (...), aby wypisać każdy argument
    (std::cout << ... << args) << std::endl;
}

int main() {
    print_all(1, 1.0, 1.0f, "Hello");
    print_all(1, 2.0);
    print_all("Test", 42, 3.14, 'A');

    return 0;
}
