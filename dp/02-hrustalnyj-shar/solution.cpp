#include <algorithm>
#include <iostream>
#include <vector>

const int cInf = 1e9;

void FillDp(std::vector<std::vector<int>>& dp, int max_throws, int levels) {
  for (int i = 0; i <= max_throws; ++i) {
    dp[i][0] = 0;
    dp[i][1] = 0;
  }
  for (int i = 1; i <= max_throws; ++i) {
    for (int j = 2; j <= levels; ++j) {
      int left = 1;
      int right = j + 1;
      while (right - left > 1) {
        int mid = (left + right) / 2;
        int diff;
        if (mid >= j) {
          diff = cInf;
        } else {
          int first_half = dp[i - 1][mid];
          int second_half = dp[i][j - mid];
          diff = first_half - second_half;
        }
        if (diff > 0) {
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
  int levels;
  int balls;
  std::cin >> levels >> balls;

  if (balls == 0) {
    std::cout << (levels == 1 ? 0 : -1);
    return 0;
  }

  int max_throws = 1;
  while ((1 << max_throws) <= levels) {
    ++max_throws;
  }

  std::vector<std::vector<int>> dp(max_throws + 1,
                                   std::vector<int>(levels + 1, cInf));
  FillDp(dp, max_throws, levels);

  int answer = dp[std::min(balls, max_throws)][levels];
  std::cout << (answer != cInf ? answer : -1);
  return 0;
}
