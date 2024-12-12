#include <iostream>
#include <vector>
#include <algorithm>


int knapsack(int W, const std::vector<int>& weights, const std::vector<int>& values, int N) {
    
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W + 1, 0));

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
   int N = 

    return 0;
}
