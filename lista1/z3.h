#ifndef Z3_H
#define Z3_H

#include <iostream>

namespace cpplab {

    template<typename T>
    class wektor {
    public:
        T* tablica;
        int pojemnosc;
        int ilosc;

        wektor() {
            tablica = new T[1];
            pojemnosc = 1;
            ilosc = 0;
        }

        ~wektor() {
            delete[] tablica;
        }

        void dodaj(const T& dane) {
            if (ilosc == pojemnosc) {
                T* tymczasowy = new T[2 * pojemnosc];

                for (int i = 0; i < pojemnosc; i++) {
                    tymczasowy[i] = tablica[i];
                }

                delete[] tablica;
                pojemnosc *= 2;
                tablica = tymczasowy;
            }

            tablica[ilosc] = dane;
            ilosc++;
        }

        T& operator[](int indeks) {
            if (indeks >= ilosc || indeks < 0) {
                throw std::out_of_range("Indeks poza zakresem");
            }
            return tablica[indeks];
        }

        const T& operator[](int indeks) const {
            if (indeks >= ilosc || indeks < 0) {
                throw std::out_of_range("Indeks poza zakresem");
            }
            return tablica[indeks];
        }

        int rozmiar() const {
            return ilosc;
        }

        int zdobadz_pojemnosc() const {
            return pojemnosc;
        }

        void wypisz() const {
            for (int i = 0; i < ilosc; i++) {
                std::cout << tablica[i] << " ";
            }
            std::cout << std::endl;
        }
    };

}

#endif // Z3_H
