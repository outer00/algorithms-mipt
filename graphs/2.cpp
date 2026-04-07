#include <iostream>
#include <vector>

const int cMax = 2 * 1e5 + 1;
std::vector<std::vector<int>> g(cMax);
std::vector<bool> visited(cMax, false);
std::vector<std::vector<int>> components(cMax);

void DFS(int v, int c) {
  visited[v] = true;
  components[c].push_back(v);
  for (auto u : g[v]) {
    if (visited[u]) {
      continue;
    }
    DFS(u, c);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int cur_comp = 0;
  for (int v = 1; v <= n; ++v) {
    if (visited[v]) {
      continue;
    }
    DFS(v, ++cur_comp);
  }
  std::cout << cur_comp << '\n';
  for (int i = 1; i <= cur_comp; ++i) {
    std::cout << components[i].size() << '\n';
    for (auto v : components[i]) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
  }
}