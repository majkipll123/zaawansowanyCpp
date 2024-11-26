#include <iostream>
#include <utility> // std::move, std::forward

namespace cpplab {
    template<typename T>
    class vector {
    public:
        T* array; // Tablica dynamiczna
        int size; // Rozmiar
        int capacity; // Pojemność

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

        // Metoda emplace_back
        template<typename... Args>
        void emplace_back(Args&&... args) {
            if (size == capacity) {
                increase_capacity();
            }
            new (&array[size++]) T(std::forward<Args>(args)...); // Tworzenie obiektu w miejscu
        }

        // Rozmiar wektora
        int get_size() const { return size; }

        // Operator indeksowania
        T& operator[](int index) { return array[index]; }
        const T& operator[](int index) const { return array[index]; }

    private:
        // Zwiększanie pojemności
        void increase_capacity() {
            capacity *= 2;
            T* new_array = new T[capacity];
            for (int i = 0; i < size; ++i) {
                new_array[i] = std::move(array[i]);
            }
            delete[] array;
            array = new_array;
        }
    };
}

struct Color {
    int r, g, b;

    // Konstruktor domyślny
    Color() : r(0), g(0), b(0) {}

    // Konstruktor parametryczny
    Color(int red, int green, int blue) : r(red), g(green), b(blue) {}

    void print() const {
        std::cout << "Color(" << r << ", " << g << ", " << b << ")" << std::endl;
    }
};

int main() {
    cpplab::vector<Color> colors;
    colors.emplace_back(255, 0, 0); // Red
    colors.emplace_back(0, 255, 0); // Green
    colors.emplace_back(0, 0, 255); // Blue

    std::cout << "Colors in the vector:" << std::endl;
    for (int i = 0; i < colors.get_size(); ++i) {
        colors[i].print();
    }

    return 0;
}
