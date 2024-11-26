#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <concepts>

// Koncept sprawdzający, czy typ posiada operator nawiasów kwadratowych []
template <typename T>
concept HasSubscriptOperator = requires(T a) {
    { a[0] };  // Sprawdza, czy można uzyskać dostęp do elementu za pomocą a[0]
};

// Koncept sprawdzający, czy typy T i U są liczbowe
template <typename T, typename U>
concept AreArithmetic = std::is_arithmetic_v<T> && std::is_arithmetic_v<U>;

// Koncept sprawdzający, czy typ ma metodę size()
template <typename T>
concept HasSizeMethod = requires(T a) {
    { a.size() } -> std::convertible_to<std::size_t>;
};

// Koncept do sprawdzenia, czy można wykonać mnożenie skalarne na dwóch typach
template <typename T, typename U>
concept ScalarMultiplicable = 
    HasSubscriptOperator<T> && // Sprawdzanie indeksowania []
    HasSubscriptOperator<U> && // Sprawdzanie indeksowania []
    AreArithmetic<typename T::value_type, typename U::value_type> && // Sprawdzanie typów liczbowych
    HasSizeMethod<T> && // Sprawdza, czy typ T ma metodę size()
    HasSizeMethod<U>;   // Sprawdza, czy typ U ma metodę size()

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
auto operator*(const T& v1, const U& v2) {
    using ResultType = typename T::value_type;  // Typ wyniku zgodny z typem elementów v1
    ResultType result = 0;
    size_t min_size = std::min(v1.size(), v2.size());

    for (size_t i = 0; i < min_size; ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

int main() {
    // Test z typami int
    cpplab::vector<int> vec1;
    vec1.add(1);
    vec1.add(2);
    vec1.add(3);

    std::vector<int> vec2 = {4, 5, 6};

    int result = vec1 * vec2;
    std::cout << "Iloczyn skalarny wektorów typu int: " << result << "\n";
// Test z bledów
    // Test z bledem
    cpplab::vector<std::string> str_vec1;
    str_vec1.add("hello");
    str_vec1.add("world");

    std::vector<std::string> str_vec2 = {"!", "!"};
     
    // blad w kompilacji 
    //auto string_result = str_vec1 * str_vec2; std::cout << "Iloczyn skalary wektorów typu string: " << string_restult <<"\n";

    
    cpplab::vector<int> incompatible_vec1;
    incompatible_vec1.add(10);
    incompatible_vec1.add(20);

    std::vector<std::string> incompatible_vec2 = {"a", "b"};
    // blad w kompilacji 
    // auto incompatible_result = incompatible_vec1 * incompatible_vec2;

    return 0;
}