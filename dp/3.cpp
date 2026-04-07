#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::string s1;
  std::string s2;
  std::cin >> s1 >> s2;

  std::vector<std::vector<int>> dp(s1.size() + 1,
                                   std::vector<int>(s2.size() + 1));

  std::vector<std::vector<std::pair<int, int>>> par(
      s1.size() + 1, std::vector<std::pair<int, int>>(s2.size() + 1, {-1, -1}));

  for (int i = 1; i <= static_cast<int>(s1.size()); ++i) {
    for (int j = 1; j <= static_cast<int>(s2.size()); ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        if (dp[i - 1][j - 1] + 1 > dp[i][j - 1]) {
          par[i][j] = std::make_pair(i, j);
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          par[i][j] = par[i][j - 1];
          dp[i][j] = dp[i][j - 1];
        }
      } else {
        if (dp[i - 1][j] > dp[i][j - 1]) {
          par[i][j] = par[i - 1][j];
          dp[i][j] = dp[i - 1][j];
        } else {
          par[i][j] = par[i][j - 1];
          dp[i][j] = dp[i][j - 1];
        }
      }
    }
  }

  std::cout << dp[s1.size()][s2.size()] << '\n';

  std::vector<int> first(dp[s1.size()][s2.size()]);
  std::vector<int> second(dp[s1.size()][s2.size()]);
  auto cur = par[s1.size()][s2.size()];
  for (int i = dp[s1.size()][s2.size()] - 1; i >= 0; --i) {
    first[i] = cur.first;
    second[i] = cur.second;
    cur = par[cur.first - 1][cur.second - 1];
  }

  for (int i = 0; i < static_cast<int>(first.size()); ++i) {
    std::cout << first[i] << ' ';
  }
  std::cout << '\n';
  for (int i = 0; i < static_cast<int>(second.size()); ++i) {
    std::cout << second[i] << ' ';
  }
}