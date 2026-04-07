#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  const int cStop = 1e5;
  int n;
  std::cin >> n;
  std::vector<int> dp(n + 1, 0);
  std::vector<std::tuple<int, int, int>> edges;
  std::vector<int> par(n + 1, -1);
  std::vector<int> ans;

  int w;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      std::cin >> w;
      if (w != cStop) {
        edges.emplace_back(i, j, w);
      }
    }
  }

  int last = INT_MAX;
  for (int i = 0; i < n; ++i) {
    last = INT_MAX;
    for (auto& edge : edges) {
      int from;
      int to;
      int weight;
      std::tie(from, to, weight) = edge;
      if (dp[from] + weight < dp[to]) {
        last = to;
        par[to] = from;
        dp[to] = dp[from] + weight;
      }
    }
  }

  if (last == INT_MAX) {
    std::cout << "NO";
    return 0;
  }
  std::cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    last = par[last];
  }
  int cur = last;
  do {
    ans.push_back(cur);
    cur = par[cur];
  } while (cur != last);

  ans.push_back(last);
  std::cout << ans.size() << '\n';
  auto rend_it = ans.rend();
  for (auto it = ans.rbegin(); it != rend_it; ++it) {
    std::cout << *it << ' ';
  }
}
