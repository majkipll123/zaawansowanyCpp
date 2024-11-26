#include <iostream>
#include <utility> // std::move, std::forward
#include <type_traits> // std::is_constructible

namespace cpplab {
    template<typename T>
    class vector {
    public:
        T* array;  // Tablica dynamiczna przechowująca dane
        int size;  // Liczba elementów w wektorze
        int capacity; // Pojemność wektora

        // Konstruktor domyślny
        vector() : array(new T[1]), size(0), capacity(1) {}

        // Konstruktor kopiujący
        vector(const vector& other) : array(new T[other.capacity]), size(other.size), capacity(other.capacity) {
            for (int i = 0; i < size; ++i) {
                array[i] = other.array[i];
            }
        }

        // Konstruktor przenoszący
        vector(vector&& other) noexcept : array(other.array), size(other.size), capacity(other.capacity) {
            other.array = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        // Operator przypisania (kopiujący)
        vector& operator=(const vector& other) {
            if (this != &other) {
                delete[] array;
                array = new T[other.capacity];
                size = other.size;
                capacity = other.capacity;
                for (int i = 0; i < size; ++i) {
                    array[i] = other.array[i];
                }
            }
            return *this;
        }

        // Operator przypisania (przenoszący)
        vector& operator=(vector&& other) noexcept {
            if (this != &other) {
                delete[] array;
                array = other.array;
                size = other.size;
                capacity = other.capacity;
                other.array = nullptr;
                other.size = 0;
                other.capacity = 0;
            }
            return *this;
        }

        // Destruktor
        ~vector() {
            delete[] array;
        }

        // Dodanie elementu przez kopię
        void add(const T& element) {
            if (size == capacity) {
                increase_capacity();
            }
            array[size++] = element;
        }

        // Metoda emplace_back
        template<typename... Args>
        void emplace_back(Args&&... args) {
            if (size == capacity) {
                increase_capacity();
            }
            new (&array[size++]) T(std::forward<Args>(args)...); // Tworzenie obiektu w miejscu
        }

        // Zwracanie rozmiaru wektora
        int get_size() const { return size; }

        // Operator indeksowania
        T& operator[](int index) { return array[index]; }
        const T& operator[](int index) const { return array[index]; }

    private:
        // Prywatna metoda zwiększająca pojemność wektora
        void increase_capacity() {
            capacity *= 2;
            T* new_array = new T[capacity];
            for (int i = 0; i < size; ++i) {
                new_array[i] = std::move(array[i]); // Przenoszenie danych
            }
            delete[] array;
            array = new_array;
        }
    };
}

// Klasa reprezentująca piksel z trzema polami r, g, b
enum class pixel : int {
    red,
    green,
    blue
};

struct Color {
    int r, g, b;

    // Konstruktor dla wygodnego tworzenia obiektów Color
    Color(int red, int green, int blue) : r(red), g(green), b(blue) {}

    // Wypisanie koloru
    void print() const {
        std::cout << "Color(" << r << ", " << g << ", " << b << ")" << std::endl;
    }
};

// Funkcja main do testowania
int main() {
    using namespace cpplab;

    // Testowanie emplace_back dla klasy Color
    vector<Color> colors;
    colors.emplace_back(255, 0, 0); // Red
    colors.emplace_back(0, 255, 0); // Green
    colors.emplace_back(0, 0, 255); // Blue

    std::cout << "Colors in the vector:" << std::endl;
    for (int i = 0; i < colors.get_size(); ++i) {
        colors[i].print();
    }

    return 0;
}
