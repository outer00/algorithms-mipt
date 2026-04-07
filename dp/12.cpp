#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int fstnum;
  int secnum;
  std::cin >> fstnum >> secnum;

  std::vector<int> first(fstnum + 1);
  std::vector<int> second(secnum + 1);
  for (int i = 1; i <= fstnum; ++i) {
    std::cin >> first[i];
  }
  for (int i = 1; i <= secnum; ++i) {
    std::cin >> second[i];
  }
  std::vector<std::vector<int>> dp(fstnum + 1, std::vector<int>(secnum + 1));
  int ans = 0;
  for (int i = 1; i <= fstnum; ++i) {
    int best = 0;
    ans = 0;
    for (int j = 1; j <= secnum; ++j) {
      dp[i][j] = std::max(dp[i - 1][j],
                          (best + 1) * static_cast<int>(first[i] == second[j]));
      if (first[i] > second[j] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
      }
      ans = std::max(dp[i][j], ans);
    }
  }
  std::cout << ans;

  return 0;
}