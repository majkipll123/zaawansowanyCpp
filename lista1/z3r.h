#ifndef Z3_H
#define Z3_H

#include <iostream>
//#include <stdexcept> // dla wyjątków

namespace cpplab {

    template<typename T>
    class vector {
    public:
        T* arr;       // Wskaźnik na dynamiczną tablicę przechowującą elementy
        int capacity; // Pojemność wektora (maksymalna liczba elementów, które może pomieścić)
        int current;  // Aktualna liczba elementów w wektorze

        // Konstruktor domyślny
        vector() {
            arr = new T[1];   // Początkowo wektor ma miejsce na 1 element
            capacity = 1;     // Pojemność wynosi 1
            current = 0;      // Aktualnie nie ma żadnych elementów
        }

        // Destruktor do zwolnienia pamięci
        ~vector() {
            delete[] arr; // Zwolnienie pamięci dynamicznie alokowanej
        }

        // Metoda dodająca element na koniec wektora
        void push_back(const T& data) {
            // Jeśli tablica jest pełna, zwiększamy pojemność dwukrotnie
            if (current == capacity) {
                T* temp = new T[2 * capacity]; // Nowa tablica o dwukrotnie większej pojemności

                // Kopiowanie elementów do nowej tablicy
                for (int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }

                // Zwolnienie starej tablicy
                delete[] arr;
                capacity *= 2; // Zwiększenie pojemności
                arr = temp;    // Ustawienie wskaźnika na nową tablicę
            }

            // Dodanie nowego elementu na koniec
            arr[current] = data;
            current++;
        }

        // Metoda dostępu do elementu (operator [])
        T& operator[](int index) {
            if (index >= current || index < 0) {
                throw std::out_of_range("Index out of range");
            }
            return arr[index];
        }

        // Zwrócenie liczby elementów w wektorze
        int size() const {
            return current;
        }

        // Zwrócenie pojemności wektora
        int get_capacity() const {
            return capacity;
        }

        // Wypisywanie zawartości wektora
        void print() const {
            for (int i = 0; i < current; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
    };

}

#endif // Z3_H
