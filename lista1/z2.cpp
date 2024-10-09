#include <iostream>
#include <vector>

template<typename T>
std::vector<T> insertion_sort(std::vector<T> vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        T key = vec[i];
        int j = i - 1;

        // Przesuwamy elementy większe od klucza o jedno miejsce do przodu
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }

        // Wstawiamy klucz na właściwe miejsce
        vec[j + 1] = key;
    }
    return vec; // Zwracamy posortowany wektor
}

int main()
{
    std::vector<int> vektor1 = {1,4,3};
    std::vector<int> posortowanyWektor = insertion_sort(vektor1);
    for (const auto& element : posortowanyWektor) 
    {
        std::cout << element << " ";
    }
}