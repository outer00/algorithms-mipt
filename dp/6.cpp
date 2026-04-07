#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<long long>> dp(n + 1,
                                         std::vector<long long>(n + 1, 0));
  for (int i = 0; i <= n; ++i) {
    dp[i][0] = 0;
    dp[0][i] = 1;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = (i >= j ? dp[i][j - 1] + dp[i - j][j / 2] : dp[i][i]);
    }
  }
  std::cout << dp[n][n];
}