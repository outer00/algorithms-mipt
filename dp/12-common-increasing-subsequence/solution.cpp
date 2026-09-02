#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int first_size;
  int second_size;
  std::cin >> first_size >> second_size;

  std::vector<int> first(first_size + 1);
  std::vector<int> second(second_size + 1);
  for (int i = 1; i <= first_size; ++i) {
    std::cin >> first[i];
  }
  for (int j = 1; j <= second_size; ++j) {
    std::cin >> second[j];
  }

  std::vector<std::vector<int>> dp(first_size + 1,
                                   std::vector<int>(second_size + 1));
  int answer = 0;
  for (int i = 1; i <= first_size; ++i) {
    int best = 0;
    answer = 0;
    for (int j = 1; j <= second_size; ++j) {
      dp[i][j] = std::max(dp[i - 1][j],
                          (best + 1) * static_cast<int>(first[i] == second[j]));
      if (first[i] > second[j] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
      }
      answer = std::max(dp[i][j], answer);
    }
  }

  std::cout << answer;
  return 0;
}
