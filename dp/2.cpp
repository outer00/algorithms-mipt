#include <algorithm>
#include <iostream>
#include <vector>

const int cInf = 1000000000;

void Fill(std::vector<std::vector<int>>& dp, int pow, int n) {
  for (int i = 0; i <= pow; ++i) {
    dp[i][0] = 0;
    dp[i][1] = 0;
  }
  for (int i = 1; i <= pow; ++i) {
    for (int j = 2; j <= n; ++j) {
      int left = 1;
      int right = j + 1;
      while (right - left > 1) {
        int mid = (left + right) / 2;
        int val;
        if (mid >= j) {
          val = cInf;
        } else {
          int first_half = dp[i - 1][mid];
          int second_half = dp[i][j - mid];
          val = first_half - second_half;
        }
        if (val > 0) {
          right = mid;
        } else {
          left = mid;
        }
      }
      dp[i][j] = std::max(dp[i - 1][left], dp[i][j - left]) + 1;
    }
  }
}

int main() {
  int n;
  int k;
  std::cin >> n >> k;
  if (k == 0) {
    if (n == 1) {
      std::cout << 0;
      return 0;
    }
    std::cout << -1;
    return 0;
  }
  int pow = 1;
  while (true) {
    if (1 << pow > n) {
      break;
    }
    ++pow;
  }
  std::vector<std::vector<int>> dp(pow + 1, std::vector<int>(n + 1, cInf));
  Fill(dp, pow, n);
  if (dp[std::min(k, pow)][n] != cInf) {
    std::cout << dp[std::min(k, pow)][n];
  } else {
    std::cout << -1;
  }
  return 0;
}
