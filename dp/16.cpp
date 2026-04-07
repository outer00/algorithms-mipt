#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cin >> a[i][j];
    }
  }
  const int cMask = (1 << n) - 1;
  const int cInf = 2e7;
  std::vector<std::vector<int>> dp(cMask + 1, std::vector<int>(n + 1, cInf));
  std::vector<std::vector<int>> par(cMask + 1, std::vector<int>(n + 1, -1));
  for (int i = 1; i <= n; ++i) {
    dp[1 << (i - 1)][i] = 0;
  }

  for (int mask = 0; mask <= cMask; ++mask) {
    for (int j = 1; j <= n; ++j) {
      if ((mask & (1 << (j - 1))) == 0) {
        continue;
      }
      for (int i = 1; i <= n; ++i) {
        if ((mask & (1 << (i - 1))) != 0) {
          continue;
        }
        if (dp[mask | (1 << (i - 1))][i] > dp[mask][j] + a[i][j]) {
          dp[mask | (1 << (i - 1))][i] = dp[mask][j] + a[i][j];
          par[mask | (1 << (i - 1))][i] = j;
        }
      }
    }
  }
  auto it = std::min_element(dp[cMask].begin(), dp[cMask].end());
  std::cout << *it << '\n';
  int ind = std::distance(dp[cMask].begin(), it);
  int mask = cMask;
  while (ind != -1) {
    std::cout << ind << ' ';
    int prev = par[mask][ind];
    mask ^= (1 << (ind - 1));
    ind = prev;
  }
}