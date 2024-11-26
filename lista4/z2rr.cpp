#include <iostream>
#include <memory>
#include <utility>

// Szablon klasy cpplab::vector
namespace cpplab {
    template <typename T>
    class vector {
    private:
        T* array;
        size_t size;
        size_t capacity;

        // Zwiększanie pojemności wektora
        void increase_capacity() {
            capacity *= 2;
            T* new_array = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_array[i] = std::move(array[i]);
            }
            delete[] array;
            array = new_array;
        }

    public:
        // Konstruktor domyślny
        vector() : array(new T[1]), size(0), capacity(1) {}

        // Destruktor
        ~vector() { delete[] array; }

        // Dodawanie nowego elementu za pomocą emplace_back()
        template <typename... Args>
        void emplace_back(Args&&... args) {
            if (size == capacity) {
                increase_capacity();
            }
            // Perfect forwarding do stworzenia obiektu na końcu
            new (&array[size]) T(std::forward<Args>(args)...);
            ++size;
        }

        // Wyświetlanie zawartości wektora
        void print() const {
            for (size_t i = 0; i < size; ++i) {
                std::cout << array[i] << " ";
            }
            std::cout << std::endl;
        }
    };
}

// Definicja klasy pixel z domyślnym konstruktorem
class pixel {
public:
    int r, g, b;

    // Domyślny konstruktor
    pixel() : r(0), g(0), b(0) {}

    // Konstruktor przyjmujący wartości r, g, b
    pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}

    // Przeciążenie operatora <<
    friend std::ostream& operator<<(std::ostream& os, const pixel& p) {
        os << "(" << p.r << ", " << p.g << ", " << p.b << ")";
        return os;
    }
};

// Funkcja main do testowania
int main() {
    cpplab::vector<pixel> v;

    // Testowanie emplace_back() z różnymi wartościami
    v.emplace_back(3, 4, 6); // Tworzy pixel(3, 4, 6)
    v.emplace_back(255, 0, 0); // Tworzy pixel(255, 0, 0)
    v.emplace_back(0, 255, 0); // Tworzy pixel(0, 255, 0)

    // Wyświetlanie zawartości wektora
    std::cout << "Zawartość wektora pixel: ";
    v.print();

    return 0;
}
