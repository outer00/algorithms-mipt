#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int count;
  std::cin >> count;

  std::vector<std::vector<int>> weight(count + 1, std::vector<int>(count + 1));
  for (int i = 1; i <= count; ++i) {
    for (int j = 1; j <= count; ++j) {
      std::cin >> weight[i][j];
    }
  }

  const int cFullMask = (1 << count) - 1;
  const int cInf = 2e7;

  std::vector<std::vector<int>> dp(cFullMask + 1,
                                   std::vector<int>(count + 1, cInf));
  std::vector<std::vector<int>> parent(cFullMask + 1,
                                       std::vector<int>(count + 1, -1));
  for (int i = 1; i <= count; ++i) {
    dp[1 << (i - 1)][i] = 0;
  }

  for (int mask = 0; mask <= cFullMask; ++mask) {
    for (int last = 1; last <= count; ++last) {
      if ((mask & (1 << (last - 1))) == 0) {
        continue;
      }
      for (int next = 1; next <= count; ++next) {
        if ((mask & (1 << (next - 1))) != 0) {
          continue;
        }
        int next_mask = mask | (1 << (next - 1));
        if (dp[next_mask][next] > dp[mask][last] + weight[next][last]) {
          dp[next_mask][next] = dp[mask][last] + weight[next][last];
          parent[next_mask][next] = last;
        }
      }
    }
  }

  auto best = std::min_element(dp[cFullMask].begin(), dp[cFullMask].end());
  std::cout << *best << '\n';

  int vertex = std::distance(dp[cFullMask].begin(), best);
  int mask = cFullMask;
  while (vertex != -1) {
    std::cout << vertex << ' ';
    int previous = parent[mask][vertex];
    mask ^= 1 << (vertex - 1);
    vertex = previous;
  }
  return 0;
}
