#include <iostream>
#include <tuple>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<bool> visited;

void Dfs(int v) {
  visited[v] = true;
  for (auto u : g[v]) {
    if (!visited[u]) {
      Dfs(u);
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<int> match(n + 1);
  std::vector<std::pair<int, int>> e;
  g.resize(n + m + 1);
  visited.resize(n + m + 1);
  for (int v = 1; v <= n; ++v) {
    int k;
    int u;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      std::cin >> u;
      e.emplace_back(v, u);
    }
  }
  for (int v = 1; v <= n; ++v) {
    std::cin >> match[v];
  }
  for (const auto& edge : e) {
    int v;
    int u;
    std::tie(v, u) = edge;
    if (match[v] != u) {
      g[v].push_back(n + u);
    } else {
      g[n + u].push_back(v);
    }
  }
  for (int v = 1; v <= n; ++v) {
    if (match[v] == 0) {
      Dfs(v);
    }
  }
  std::vector<int> left;
  int l = 0;
  std::vector<int> right;
  int r = 0;
  for (int v = 1; v <= n; ++v) {
    if (!visited[v]) {
      left.push_back(v);
      ++l;
    }
  }
  for (int v = n + 1; v <= n + m; ++v) {
    if (visited[v]) {
      right.push_back(v - n);
      ++r;
    }
  }
  std::cout << l + r << "\n";
  std::cout << l << ' ';
  for (auto v : left) {
    std::cout << v << ' ';
  }
  std::cout << "\n" << r << ' ';
  for (auto v : right) {
    std::cout << v << ' ';
  }
  return 0;
}
