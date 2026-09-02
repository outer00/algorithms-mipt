#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::string s;
  std::string t;
  std::cin >> s >> t;

  int s_size = static_cast<int>(s.size());
  int t_size = static_cast<int>(t.size());

  std::vector<std::vector<int>> dp(s_size + 1, std::vector<int>(t_size + 1));
  std::vector<std::vector<std::pair<int, int>>> parent(
      s_size + 1, std::vector<std::pair<int, int>>(t_size + 1, {-1, -1}));

  for (int i = 1; i <= s_size; ++i) {
    for (int j = 1; j <= t_size; ++j) {
      if (s[i - 1] == t[j - 1] && dp[i - 1][j - 1] + 1 > dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        parent[i][j] = {i, j};
      } else if (s[i - 1] != t[j - 1] && dp[i - 1][j] > dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        parent[i][j] = parent[i - 1][j];
      } else {
        dp[i][j] = dp[i][j - 1];
        parent[i][j] = parent[i][j - 1];
      }
    }
  }

  int length = dp[s_size][t_size];
  std::cout << length << '\n';

  std::vector<int> s_indices(length);
  std::vector<int> t_indices(length);
  auto current = parent[s_size][t_size];
  for (int i = length - 1; i >= 0; --i) {
    s_indices[i] = current.first;
    t_indices[i] = current.second;
    current = parent[current.first - 1][current.second - 1];
  }

  for (int index : s_indices) {
    std::cout << index << ' ';
  }
  std::cout << '\n';
  for (int index : t_indices) {
    std::cout << index << ' ';
  }
  return 0;
}
