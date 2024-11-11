#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

// Koncept do sprawdzenia, czy typy można mnożyć i dodawać, aby uzyskać wynik skalarny
template <typename T, typename U>
concept ScalarMultiplicable = requires(T a, U b) {
    { a * b } -> std::convertible_to<T>;   // Sprawdzenie, czy a * b jest poprawne i daje wynik typu T
    { T{} + (a * b) } -> std::convertible_to<T>; // Sprawdzenie, czy można dodać iloczyny
};

namespace cpplab {
    template<typename T>
    class vector {
    public:
        T* array;  // tablica przechowująca elementy
        int size;  // rozmiar wektora

        // Konstruktor domyślny
        vector() : array(new T[1]), size(0) {}

        // Dodawanie elementu do wektora
        void add(const T& element) {
            T* new_array = new T[size + 1];
            for (int i = 0; i < size; ++i)
                new_array[i] = array[i];
            new_array[size++] = element;
            delete[] array;
            array = new_array;
        }

        // Destruktor
        ~vector() { delete[] array; }

        // Zwraca rozmiar wektora
        int get_size() const { return size; }

        // Operator indeksowania (wersja zwykła i stała)
        T& operator[](int index) { return array[index]; }
        const T& operator[](int index) const { return array[index]; }
    };
}

// Operator mnożenia skalarnego z użyciem konceptu ScalarMultiplicable
template <typename T, typename U>
requires ScalarMultiplicable<T, U>
T operator*(const cpplab::vector<T>& v1, const std::vector<U>& v2) {
    T result = 0;
    size_t min_size = std::min(v1.get_size(), static_cast<int>(v2.size()));

    for (size_t i = 0; i < min_size; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Operator mnożenia skalarnego w odwrotnej kolejności argumentów
template <typename T, typename U>
requires ScalarMultiplicable<T, U>
T operator*(const std::vector<U>& v2, const cpplab::vector<T>& v1) {
    return v1 * v2;
}

int main() {
    // Test z typami całkowitymi
    cpplab::vector<int> vec1;
    vec1.add(1);
    vec1.add(2);
    vec1.add(3);

    std::vector<int> vec2 = {4, 5, 6};

    int result = vec1 * vec2;
    std::cout << "Iloczyn skalarny wektorów typu int: " << result << "\n";

    // Test z typem std::string (powinien spowodować błąd kompilacji)
    cpplab::vector<std::string> str_vec1;
    str_vec1.add("hello");
    str_vec1.add("world");

    std::vector<std::string> str_vec2 = {"!", "!"};

    // Odkomentowanie poniższej linii powinno spowodować błąd kompilacji
     auto string_result = str_vec1 * str_vec2; std::cout << "Iloczyn skalary wektorów typu string: " << string_restult <<"\n";

    // Test z niekompatybilnymi typami (np. wektor int i wektor std::string)
    cpplab::vector<int> incompatible_vec1;
    incompatible_vec1.add(10);
    incompatible_vec1.add(20);

    std::vector<std::string> incompatible_vec2 = {"a", "b"};

    // Odkomentowanie poniższej linii powinno spowodować błąd kompilacji
    // auto incompatible_result = incompatible_vec1 * incompatible_vec2;

    return 0;
}
