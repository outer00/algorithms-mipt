#include <limits.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

struct Hash {
  std::size_t operator()(const std::pair<int, int>& p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

int n;
std::pair<bool, int> RunFlow(int from, int to, int flow,
                             std::vector<bool>& visited,
                             std::vector<std::vector<int>>& g) {
  if (from == to) {
    return {true, flow};
  }
  visited[from] = true;
  for (int u = 1; u <= n; ++u) {
    if (g[from][u] > 0 && !visited[u]) {
      auto res = RunFlow(u, to, std::min(g[from][u], flow), visited, g);
      if (res.first) {
        g[from][u] -= res.second;
        g[u][from] += res.second;
        return {true, res.second};
      }
    }
  }
  return {false, -1};
}

void DFS(int u, std::vector<bool>& visited, std::vector<std::vector<int>>& g) {
  visited[u] = true;
  for (int v = 1; v <= n; ++v) {
    if (!visited[v] && g[u][v] > 0) {
      DFS(v, visited, g);
    }
  }
}

int main() {
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1, 0));
  std::unordered_map<std::pair<int, int>, int, Hash> e;
  std::vector<bool> visited(n + 1, false);
  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    e[std::make_pair(u, v)] = e[std::make_pair(v, u)] = i;
    g[u][v] = c;
    g[v][u] = c;
  }
  int mincut = 0;
  std::pair<bool, int> res;
  while ([&]() {
    res = RunFlow(1, n, INT_MAX, visited, g);
    return res.first;
  }()) {
    mincut += res.second;
    visited.assign(n + 1, false);
  }
  DFS(1, visited, g);
  std::set<int> ans;
  for (const auto& edge : e) {
    if (visited[edge.first.first] != visited[edge.first.second]) {
      ans.insert(edge.second);
    }
  }
  std::cout << ans.size() << ' ' << mincut << '\n';
  for (auto edge : ans) {
    std::cout << edge << ' ';
  }
}