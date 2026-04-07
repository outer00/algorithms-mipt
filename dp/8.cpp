#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string u;
  std::string v;
  int k;
  std::cin >> u >> v >> k;
  int n = static_cast<int>(u.size());
  int m = static_cast<int>(v.size());
  u = ' ' + u;
  v = ' ' + v;

  if (std::max(n, m) - std::min(n, m) > k) {
    std::cout << -1;
    return 0;
  }

  std::vector<std::vector<std::vector<int>>> dp(
      m + 1, std::vector<std::vector<int>>(k + 1, std::vector<int>(k + 1, 0)));

  for (int i = 1; i <= m; ++i) {
    for (int rm_ops = 0; rm_ops <= std::min(k, n); ++rm_ops) {
      for (int add_ops = 0; add_ops <= std::min(k - rm_ops, i); ++add_ops) {
        int l = i + rm_ops - add_ops;
        dp[i][rm_ops][add_ops] =
            std::max({(rm_ops > 0 ? dp[i][rm_ops - 1][add_ops] : 0),
                      (add_ops > 0 ? dp[i - 1][rm_ops][add_ops - 1] + 1 : 0),
                      ((l - 1) * (n - l) >= 0
                           ? dp[i - 1][rm_ops][add_ops] + (u[l] == v[i] ? 1 : 0)
                           : 0)});
      }
    }
  }

  int lcs = -1;
  for (int rm_ops = 0; rm_ops <= std::min(k, n); ++rm_ops) {
    for (int add_ops = 0; add_ops <= std::min(k - rm_ops, m); ++add_ops) {
      if (m + rm_ops - add_ops != n) {
        continue;
      }
      lcs = std::max(
          lcs, std::min(m, dp[m][rm_ops][add_ops] + k - rm_ops - add_ops));
    }
  }

  std::cout << (lcs == -1 ? lcs : m - lcs);
}