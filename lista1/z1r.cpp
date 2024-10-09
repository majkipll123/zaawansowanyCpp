#include <iostream>
#include <functional> // dla std::function

template <typename T, typename C>
T my_max(T a, T b, C comp) {
    return comp(a, b) ? b : a;
}

int main() {
    // Przykład użycia z typami int
    auto int_comp = [](int x, int y) { return x < y; };
    std::cout << "Max(3, 5) = " << my_max(3, 5, int_comp) << std::endl; // powinno zwrócić 5

    // Przykład użycia z typami double
    auto double_comp = [](double x, double y) { return x < y; };
    std::cout << "Max(2.5, 1.5) = " << my_max(2.5, 1.5, double_comp) << std::endl; // powinno zwrócić 2.5

    // Przykład użycia z typami string
    auto string_comp = [](const std::string &x, const std::string &y) { return x < y; };
    std::cout << "Max('apple', 'banana') = " << my_max(std::string("apple"), std::string("banana"), string_comp) << std::endl; // powinno zwrócić "banana"

    return 0;
}