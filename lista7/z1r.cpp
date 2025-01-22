#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <iterator>
#include <functional>
#include <future>
#include <numeric>
#include <stdexcept>

// Funkcja obliczająca iloczyn skalarny
void dot_product(const std::vector<double>& vec1, const std::vector<double>& vec2, std::promise<double> result_promise) {
    try {
        if (vec1.empty() || vec2.empty()) {
            throw std::invalid_argument("Wektory nie mogą być puste.");
        }
        if (vec1.size() != vec2.size()) {
            throw std::invalid_argument("Wektory muszą mieć ten sam rozmiar.");
        }

        double result = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0.0);
        result_promise.set_value(result);
    } catch (const std::exception& e) {
        result_promise.set_exception(std::current_exception());
    }
}

int main() {
    // Tworzenie losowych wektorów do obliczeń
    const size_t vector_size = 100;
    const size_t num_threads = 10;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(1.0, 10.0);

    std::vector<std::vector<double>> vectors1(num_threads, std::vector<double>(vector_size));
    std::vector<std::vector<double>> vectors2(num_threads, std::vector<double>(vector_size));

    for (size_t i = 0; i < num_threads; ++i) {
        std::generate(vectors1[i].begin(), vectors1[i].end(), [&]() { return dis(gen); });
        std::generate(vectors2[i].begin(), vectors2[i].end(), [&]() { return dis(gen); });
    }

    // Tworzenie obiektów std::promise i std::future
    std::vector<std::promise<double>> promises(num_threads);
    std::vector<std::future<double>> futures;

    for (auto& promise : promises) {
        futures.push_back(promise.get_future());
    }

    // Uruchamianie wątków
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back(dot_product, std::cref(vectors1[i]), std::cref(vectors2[i]), std::move(promises[i]));
    }

    // Czekanie na wyniki i sumowanie
    double total_sum = 0.0;
    for (size_t i = 0; i < num_threads; ++i) {
        try {
            total_sum += futures[i].get();
        } catch (const std::exception& e) {
            std::cerr << "Błąd w wątku " << i << ": " << e.what() << std::endl;
        }
    }

    // Dołączanie wątków
    for (auto& thread : threads) {
        thread.join();
    }

    // Wyświetlenie wyniku
    std::cout << "Suma iloczynów skalarnych: " << total_sum << std::endl;

    return 0;
}
