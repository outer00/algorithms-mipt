#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

int main() {
  int n;
  int m;
  int s;
  std::cin >> n >> m >> s;
  std::vector<std::vector<std::tuple<int, int, int>>> g(n + 1);
  std::vector<int> min_t(n + 1, INT_MAX);
  std::vector<int> cost((s + 1) * (n + 1), INT_MAX);
  std::vector<int> prev((s + 1) * (n + 1), -1);

  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int c;
    int t;
    std::cin >> u >> v >> c >> t;
    --u;
    --v;
    g[u].emplace_back(v, c, t);
    g[v].emplace_back(u, c, t);
  }
  std::set<std::pair<int, int>> order;
  order.emplace(0, n - 1);
  min_t[n - 1] = 0;
  while (!order.empty()) {
    int t;
    int v;
    std::tie(t, v) = *order.begin();
    order.erase(order.begin());
    if (t > min_t[v]) {
      continue;
    }
    min_t[v] = t;
    for (const auto& edge : g[v]) {
      int to;
      int t2;
      std::tie(to, std::ignore, t2) = edge;
      if (t + t2 < min_t[to]) {
        order.emplace(t + t2, to);
      }
    }
  }
  order.emplace(0, 0);
  cost[0] = 0;
  while (!order.empty()) {
    int c;
    int t;
    std::tie(c, t) = *order.begin();
    order.erase(order.begin());
    if (c > cost[t]) {
      continue;
    }
    for (const auto& edge : g[t / (s + 1)]) {
      int to;
      int c2;
      int time;
      std::tie(to, c2, time) = edge;
      if (t % (s + 1) + time + min_t[to] > s) {
        continue;
      }
      int next_vertex = to * (s + 1) + t % (s + 1) + time;
      if (c + c2 < cost[next_vertex]) {
        order.emplace(c + c2, next_vertex);
        cost[next_vertex] = c + c2;
        prev[next_vertex] = t;
      }
    }
  }

  int cur = -1;
  int min_cost = INT_MAX;
  for (int cur_t = 0; cur_t <= s; ++cur_t) {
    int idx = (n - 1) * (s + 1) + cur_t;
    if (cost[idx] < min_cost) {
      min_cost = cost[idx];
      cur = idx;
    }
  }
  if (min_cost == INT_MAX) {
    std::cout << "-1\n";
    return 0;
  }
  std::cout << min_cost << "\n";
  std::vector<int> path;
  path.push_back(cur / (s + 1) + 1);
  while (prev[cur] != -1) {
    cur = prev[cur];
    path.push_back(cur / (s + 1) + 1);
  }
  std::cout << path.size() << "\n";
  auto rend_it = path.rend();
  for (auto it = path.rbegin(); it != rend_it; ++it) {
    std::cout << *it << " ";
  }
}