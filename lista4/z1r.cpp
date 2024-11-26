#include <iostream>
#include <utility> // std::move

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
            other.array = nullptr;  // Zmieniamy wskaźnik, aby uniknąć podwójnego zwolnienia
            other.size = 0;
            other.capacity = 0;
        }

        // Operator przypisania (kopiujący)
        vector& operator=(const vector& other) {
            if (this != &other) { // Sprawdzenie samokopiowania
                delete[] array; // Zwolnienie istniejącej pamięci
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
            if (this != &other) { // Sprawdzenie samoprzeniesienia
                delete[] array; // Zwolnienie istniejącej pamięci
                array = other.array;
                size = other.size;
                capacity = other.capacity;

                other.array = nullptr; // Zmieniamy wskaźnik, aby uniknąć podwójnego zwolnienia
                other.size = 0;
                other.capacity = 0;
            }
            return *this;
        }

        // Destruktor
        ~vector() {
            delete[] array; // Zwolnienie pamięci
        }

        // Dodanie elementu
        void add(const T& element) {
            if (size == capacity) {
                // Zwiększenie pojemności
                capacity *= 2;
                T* new_array = new T[capacity];
                for (int i = 0; i < size; ++i) {
                    new_array[i] = array[i];
                }
                delete[] array;
                array = new_array;
            }
            array[size++] = element;
        }

        // Zwracanie rozmiaru wektora
        int get_size() const { return size; }

        // Operator indeksowania
        T& operator[](int index) { return array[index]; }
        const T& operator[](int index) const { return array[index]; }
    };
}

// Testy w funkcji main
int main() {
    using namespace cpplab;

    // Testowanie konstruktorów
    vector<int> vec1;
    vec1.add(1);
    vec1.add(2);
    vec1.add(3);

    std::cout << "Oryginalny wektor vec1: ";
    for (int i = 0; i < vec1.get_size(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    // Testowanie konstruktora kopiującego
    vector<int> vec2 = vec1;
    std::cout << "Skopiowany wektor vec2: ";
    for (int i = 0; i < vec2.get_size(); ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    // Testowanie operatora przypisania (kopiującego)
    vector<int> vec3;
    vec3 = vec1;
    std::cout << "Wektor vec3 po przypisaniu (kopiowanie): ";
    for (int i = 0; i < vec3.get_size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << std::endl;

    // Testowanie konstruktora przenoszącego
    vector<int> vec4 = std::move(vec1);
    std::cout << "Wektor vec4 po przeniesieniu: ";
    for (int i = 0; i < vec4.get_size(); ++i) {
        std::cout << vec4[i] << " ";
    }
    std::cout << std::endl;

    // Testowanie operatora przypisania (przenoszącego)
    vector<int> vec5;
    vec5 = std::move(vec2);
    std::cout << "Wektor vec5 po przypisaniu (przenoszenie): ";
    for (int i = 0; i < vec5.get_size(); ++i) {
        std::cout << vec5[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
