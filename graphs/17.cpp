#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int main() {
  const int cMaxN = 1e6;
  const int cInf = 1e9;
  int n;
  int u;
  int d;
  int i;
  int o;
  int k;
  std::cin >> n >> u >> d >> i >> o >> k;

  std::vector<std::vector<std::pair<int, int>>> g(cMaxN + k + 1);
  std::vector<int> dist(cMaxN + k + 1, cInf);
  std::set<int> s;
  s.insert(1);
  s.insert(n);
  for (int tp = 1; tp <= k; ++tp) {
    int cnt;
    std::cin >> cnt;
    for (int j = 0; j < cnt; ++j) {
      int v;
      std::cin >> v;
      g[cMaxN + tp].emplace_back(v, o);
      g[v].emplace_back(cMaxN + tp, i);
      s.insert(v);
    }
  }

  int prev = *s.begin();
  for (int v : s) {
    g[v].emplace_back(prev, d * (v - prev));
    g[prev].emplace_back(v, u * (v - prev));
    prev = v;
  }

  std::set<std::pair<int, int>> queue;
  queue.emplace(0, 1);
  dist[1] = 0;
  while (!queue.empty()) {
    int cost;
    int cur;
    std::tie(cost, cur) = *queue.begin();
    queue.erase(queue.begin());
    if (dist[cur] < cost) {
      continue;
    }
    for (const auto& edge : g[cur]) {
      int to;
      int weight;
      std::tie(to, weight) = edge;
      if (cost + weight < dist[to]) {
        dist[to] = cost + weight;
        queue.emplace(dist[to], to);
      }
    }
  }
  std::cout << dist[n] << "\n";
  return 0;
}
