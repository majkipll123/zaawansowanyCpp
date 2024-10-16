#ifndef Z3_H
#define Z3_H

#include <iostream>
//#include <stdexcept> // wyjątki

namespace cpplab {

    template<typename T>
    class wektor {
    public:
        T* tablica;       // tablica
        int pojemnosc;    // pojemność
        int ilosc;        // aktualna liczba elementów

        // Konstruktor domyślny
        wektor() {
            tablica = new T[1];   // Miejsce na 1 element
            pojemnosc = 1;        // Pojemność 1
            ilosc = 0;            // Brak elementów
        }

        // Destruktor
        ~wektor() {
            delete[] tablica; // Zwolnienie pamięci
        }

        // Dodanie elementu
        void dodaj(const T& dane) {
            // Jeśli pełny, zwiększ pojemność
            if (ilosc == pojemnosc) {
                T* tymczasowy = new T[2 * pojemnosc]; // Nowa, większa tablica

                // Kopiowanie danych
                for (int i = 0; i < pojemnosc; i++) {
                    tymczasowy[i] = tablica[i];
                }

                // Zwolnienie starej tablicy
                delete[] tablica;
                pojemnosc *= 2; // Zwiększ pojemność
                tablica = tymczasowy; // Ustaw nową tablicę
            }

            // Dodaj nowy element
            tablica[ilosc] = dane;
            ilosc++;
        }

        // Dostęp do elementu (operator [])
        T& operator[](int indeks) {
            if (indeks >= ilosc || indeks < 0) {
                throw std::out_of_range("Indeks poza zakresem");
            }
            return tablica[indeks];
        }

        // Dodajemy wersję const operator[] dla obiektów stałych
        const T& operator[](int indeks) const {
            if (indeks >= ilosc || indeks < 0) {
                throw std::out_of_range("Indeks poza zakresem");
            }
            return tablica[indeks];
        }

        // Zwrócenie liczby elementów
        int rozmiar() const {
            return ilosc;
        }

        // Zwrócenie pojemności
        int zdobadz_pojemnosc() const {
            return pojemnosc;
        }

        // Wypisanie zawartości
        void wypisz() const {
            for (int i = 0; i < ilosc; i++) {
                std::cout << tablica[i] << " ";
            }
            std::cout << std::endl;
        }
    };

}

#endif // Z3_H
