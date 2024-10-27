#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cctype> // dla std::isdigit

// sortowanie przez wstawianie
template<typename T>
void insertion_sort(std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        T key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }
}

//porzadek normalny
bool natural_compare(const std::string& a, const std::string& b) {
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) { 
        
        if (std::isdigit(a[i]) && std::isdigit(b[j])) {
            
            size_t num_start_a = i, num_start_b = j;
            while (i < a.size() && std::isdigit(a[i])) i++;
            while (j < b.size() && std::isdigit(b[j])) j++;
            
            int num_a = std::stoi(a.substr(num_start_a, i - num_start_a));
            int num_b = std::stoi(b.substr(num_start_b, j - num_start_b));
            
           
            if (num_a != num_b) return num_a < num_b;
        } else {
            
            if (a[i] != b[j]) return a[i] < b[j];
            i++;
            j++;
        }
    }
    // Jeśli jeden ciąg jest prefiksem drugiego
    return a.size() < b.size();
}

// Specjalizacja dla std::string
template<>
void insertion_sort<std::string>(std::vector<std::string>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        std::string key = vec[i];
        int j = i - 1;

        // Przesuwam elementy większe w porządku naturalnym
        while (j >= 0 && natural_compare(key, vec[j])) {
            vec[j + 1] = vec[j];
            --j;
        }

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
    std::vector<std::string> test1 = {"mirokox14","natu1ralsigma18","natu2ralsigma18","szczeryogon72","DaddyTateTo1B","RNTTo1B","1","10","21","2","1000x","mirokox13"};

    std::cout << "Przed sortowaniem (test1): ";
    print_vector(test1);

    insertion_sort(test1);

    std::cout << "Po sortowaniu naturalnym (test1): ";
    print_vector(test1);

    return 0;
}
