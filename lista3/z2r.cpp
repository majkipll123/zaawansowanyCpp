#include <iostream>
#include <vector>
#include <algorithm> // std::sort

// Szablon funkcji as_sorted_view
template <typename T>
void as_sorted_view(const std::vector<T>& vec) {
    // Tworzymy kopię oryginalnego wektora
    std::vector<T> sorted_vec = vec;

    // Sortujemy kopię wektora
    std::sort(sorted_vec.begin(), sorted_vec.end());

    // Wyświetlamy posortowane elementy
    for (const auto& element : sorted_vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test dla wektora int
    std::vector<int> vec1 = {5, 2, 8, 1, 4};
    std::cout << "Oryginalny wektor: ";
    for (const auto& elem : vec1) {
        std::cout << elem << " ";
    }
    std::cout << "\nPosortowany widok: ";
    as_sorted_view(vec1);

    // Test dla wektora typu double
    std::vector<double> vec2 = {3.1, 1.4, 2.2, 5.9, 0.8};
    std::cout << "Oryginalny wektor: ";
    for (const auto& elem : vec2) {
        std::cout << elem << " ";
    }
    std::cout << "\nPosortowany widok: ";
    as_sorted_view(vec2);

    // Test dla wektora std::string
    std::vector<std::string> vec3 = {"apple", "orange", "banana", "grape"};
    std::cout << "Oryginalny wektor: ";
    for (const auto& elem : vec3) {
        std::cout << elem << " ";
    }
    std::cout << "\nPosortowany widok: ";
    as_sorted_view(vec3);

    return 0;
}
