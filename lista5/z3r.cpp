#include <iostream>
#include <vector>
#include <algorithm>

// Funkcja rozwiązująca problem plecakowy
int knapsack(int W, const std::vector<int>& weights, const std::vector<int>& values, int N) {
    // Tworzymy tablicę dp
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W + 1, 0));

    //  tablica dp
    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[N][W];
}

int main() {
    int N = 4; // Liczba skarbów
    int W = 7; // Maksymalna waga
    std::vector<int> weights = {1, 3, 4, 5}; // Wagi skarbów
    std::vector<int> values = {1, 4, 5, 7};  // Ceny skarbów

    int M = 4; // Liczba skarbów
    int X = 7; // Maksymalna waga
    std::vector<int> weights2 = {1, 3, 4, 5, 7, 8, 12};
    std::vector<int> values2 = {1, 4, 5, 7, 7, 8, 10};  

    int max_value = knapsack(W, weights, values, N);

     int max_value2 = knapsack(X, weights2, values2, M);

    std::cout << "Maksymalna wartość: " << max_value << "\n";
    std::cout << "Maksymalna wartość: " << max_value2 << "\n";

    return 0;
}
