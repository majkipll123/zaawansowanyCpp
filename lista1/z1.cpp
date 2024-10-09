#include <iostream>

// Szablon funkcji my_max, która przyjmuje dwie wartości a i b oraz funkcję porównującą (comp).
// Zwraca większą wartość na podstawie wyniku funkcji porównującej utworzonej za pomocą lambdy.
template<typename T, typename C>
T my_max(T a, T b, C comp)
{
    return comp(a, b) ? b : a; // funkcja comp porównuje 2 wartości, zwraca true jeśli b większe, w przeciwnym razie a
}

int main() {

    int x, y;
    std::cout << "Podaj 1 liczbe do porownania intow \n";
    std::cin >> x;
    std::cout << "Podaj 2 liczbe do porownania intow \n";
    std::cin >> y;

    double a, b;
    std::cout << "Podaj 1 liczbe do porownania doubli \n";
    std::cin >> a;
    std::cout << "Podaj 2 liczbe do porownania doubli \n";
    std::cin >> b;

    std::string c, d;
    std::cout << "Podaj 1 ciag znakow do porownania stringow \n";
    std::cin >> c;
    std::cout << "Podaj 2 ciag znakow do porownania stringow\n";
    std::cin >> d;

    auto KompIntow = [](int x, int y) { return x < y; };      
    auto KompFloatow = [](float x, float y) { return x < y; };    
    auto KompStringow = [](const std::string &x, const std::string &y) { return x < y; };  

    std::cout << "Tu masz wyniki operacji:\n"; 
    std::cout << my_max(x, y, KompIntow) << "\n";
    std::cout << my_max(a, b, KompFloatow) << "\n";
    std::cout << my_max(c, d, KompStringow) << "\n";
}
