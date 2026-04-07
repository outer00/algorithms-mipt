#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<std::vector<int>> dp(2, std::vector<int>(n, INT_MAX));
  dp[0][0] = dp[1][0] = a[0];
  int up_ind = 1;
  int down_ind = 1;
  for (int i = 1; i < n; ++i) {
    if (a[i] > a[i - 1]) {
      for (int j = up_ind; j < down_ind; ++j) {
        dp[0][j] = dp[1][j];
      }
      dp[0][(up_ind = down_ind)++] = a[i];
    } else if (a[i] < a[i - 1]) {
      for (int j = down_ind; j < up_ind; ++j) {
        dp[1][j] = dp[0][j];
      }
      dp[1][(down_ind = up_ind)++] = a[i];
    }
  }
  if (up_ind > down_ind) {
    std::cout << up_ind << '\n';
    for (int i = 0; i < up_ind; ++i) {
      std::cout << dp[0][i] << ' ';
    }
  } else {
    std::cout << down_ind << '\n';
    for (int i = 0; i < down_ind; ++i) {
      std::cout << dp[1][i] << ' ';
    }
  }
}