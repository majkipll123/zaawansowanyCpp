#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cctype> // dla std::isdigit

// Ogólny szablon funkcji sortującej przez wstawianie
template<typename T>
void insertion_sort(std::vector<T>& vec) {
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
}

// Funkcja porównująca dwa napisy w porządku naturalnym
bool natural_compare(const std::string& a, const std::string& b) {
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) { 
        // Sprawdź, czy mamy liczby w obu napisach
        if (std::isdigit(a[i]) && std::isdigit(b[j])) {
            // Parsujemy liczby
            size_t num_start_a = i, num_start_b = j;
            while (i < a.size() && std::isdigit(a[i])) i++;
            while (j < b.size() && std::isdigit(b[j])) j++;
            
            int num_a = std::stoi(a.substr(num_start_a, i - num_start_a));
            int num_b = std::stoi(b.substr(num_start_b, j - num_start_b));
            
            // Porównanie liczb
            if (num_a != num_b) return num_a < num_b;
        } else {
            // Porównanie znak po znaku, jeśli nie są liczbami
            if (a[i] != b[j]) return a[i] < b[j];
            i++;
            j++;
        }
    }
    // Jeśli jeden ciąg jest prefiksem drugiego
    return a.size() < b.size();
}

// Specjalizacja funkcji sortującej dla std::string (pełna specjalizacja)
template<>
void insertion_sort<std::string>(std::vector<std::string>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        std::string key = vec[i];
        int j = i - 1;

        // Przesuwamy elementy większe w porządku naturalnym
        while (j >= 0 && natural_compare(key, vec[j])) {
            vec[j + 1] = vec[j];
            --j;
        }

        // Wstawiamy klucz na właściwe miejsce
        vec[j + 1] = key;
    }
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> files = {"mirokox14","natu1ralsigma18","natu2ralsigma18","szczeryogon72","DaddyTateTo1B","RNTTo1B","1","10","21","2","1000x","mirokox13"};

    std::cout << "Przed sortowaniem (files): ";
    print_vector(files);

    // Sortowanie według porządku naturalnego
    insertion_sort(files);

    std::cout << "Po sortowaniu naturalnym (files): ";
    print_vector(files);

    return 0;
}
