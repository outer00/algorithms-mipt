#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string u;
  std::string v;
  int budget;
  std::cin >> u >> v >> budget;

  int u_size = static_cast<int>(u.size());
  int v_size = static_cast<int>(v.size());
  u = ' ' + u;
  v = ' ' + v;

  if (std::abs(u_size - v_size) > budget) {
    std::cout << -1;
    return 0;
  }

  std::vector<std::vector<std::vector<int>>> dp(
      v_size + 1,
      std::vector<std::vector<int>>(budget + 1, std::vector<int>(budget + 1, 0)));

  for (int i = 1; i <= v_size; ++i) {
    for (int removals = 0; removals <= std::min(budget, u_size); ++removals) {
      for (int insertions = 0; insertions <= std::min(budget - removals, i);
           ++insertions) {
        int position = i + removals - insertions;
        int keep_match =
            position >= 1 && position <= u_size
                ? dp[i - 1][removals][insertions] + (u[position] == v[i] ? 1 : 0)
                : 0;
        dp[i][removals][insertions] = std::max(
            {removals > 0 ? dp[i][removals - 1][insertions] : 0,
             insertions > 0 ? dp[i - 1][removals][insertions - 1] + 1 : 0,
             keep_match});
      }
    }
  }

  int best = -1;
  for (int removals = 0; removals <= std::min(budget, u_size); ++removals) {
    for (int insertions = 0; insertions <= std::min(budget - removals, v_size);
         ++insertions) {
      if (v_size + removals - insertions != u_size) {
        continue;
      }
      best = std::max(best, std::min(v_size, dp[v_size][removals][insertions] +
                                                 budget - removals - insertions));
    }
  }

  std::cout << (best == -1 ? best : v_size - best);
  return 0;
}
