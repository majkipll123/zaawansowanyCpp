#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <iterator>
#include <functional>

void sort_half(std::vector<int>& vec, size_t start, size_t end) {
    std::sort(vec.begin() + start, vec.begin() + end);
}

int main() {
    // Tworzenie wektora losowych liczb
    const size_t size = 1000;
    std::vector<int> vec(size);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 1000);
    
    std::generate(vec.begin(), vec.end(), [&]() { return dis(gen); });

    // Wyświetlenie pierwszych 500 elementów przed sortowaniem
    std::cout << "Przed sortowaniem (cały wektor): \n";
    std::copy(vec.begin(), vec.begin() + 1000, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // Wyznaczenie punktu podziału
    size_t mid = size / 2;

    // Uruchomienie dwóch wątków sortujących połowy wektora
    std::thread t1(sort_half, std::ref(vec), 0, mid);
    std::thread t2(sort_half, std::ref(vec), mid, size);

    t1.join();
    t2.join();

    /* Wyświetlenie pierwszych 500 elementów po sortowaniu połowy
    std::cout << "Po sortowaniu połówek pierwszej czesci wektora \n" ;
    std::copy(vec.begin(), vec.begin() + 500, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    poprzednia wersja gorzej sie czytało w konsolecie teraz chyba lepiej
    
    // Wyświetlenie drugich 500 elementów po sortowaniu połowy
    std::cout << "Po sortowaniu połówek drugiej czesci wektora \n" ;
    std::copy(vec.begin()+500, vec.begin() + 1000, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    */

    // Wyświetlenie całego wektora
    std::cout << "Po sortowaniu połówek drugiej czesci wektora \n" ;
    std::copy(vec.begin(), vec.begin() + 1000, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    return 0;
}
