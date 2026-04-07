#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;
  std::vector<int> weights(n + 1);
  std::vector<int> costs(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> weights[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> costs[i];
  }
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
  std::vector<std::vector<std::pair<int, int>>> par(
      n + 1, std::vector<std::pair<int, int>>(m + 1, {0, 0}));
  for (int i = 1; i <= n; ++i) {
    for (int w = 1; w <= m; ++w) {
      dp[i][w] = dp[i - 1][w];
      par[i][w] = std::make_pair(i - 1, w);
      if (w >= weights[i] && dp[i][w] < dp[i - 1][w - weights[i]] + costs[i]) {
        dp[i][w] = dp[i - 1][w - weights[i]] + costs[i];
        par[i][w] = std::make_pair(i - 1, w - weights[i]);
      }
    }
  }
  auto ans = par[n][m];
  if (par[n][m].second != m) {
    std::cout << n << '\n';
  }
  while (true) {
    if (par[ans.first][ans.second].second != ans.second && ans.first != 0) {
      std::cout << ans.first << '\n';
    }
    ans = par[ans.first][ans.second];
    if (ans.first == 0 || ans.second == 0) {
      break;
    }
  }
}
