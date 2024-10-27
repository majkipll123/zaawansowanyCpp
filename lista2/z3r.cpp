#include <iostream>

template<typename T, typename... Args>
void print_all(T first, Args... args) {
    std::cout << first;
    if constexpr (sizeof...(args) > 0) {
        std::cout << " "; 
        print_all(args...); 
    } else {
        std::cout << "\n"; // Nowa linia, gdy skończymy wypisywanie
    }
}

int main() {
    print_all(1, 1.0, 1.0f, "Hello");
    print_all(1, 2.0, 2);
    print_all("Studenciak", 47, 3.14, 'A');
    print_all("Pojedynczy argument");

    return 0;
}