#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

const int cMax = 1e5 + 1;
std::vector<std::vector<int>> g(cMax);
std::vector<std::vector<int>> reverse_g(cMax);
std::vector<bool> visited(cMax, false);
std::vector<int> tout(cMax);
std::vector<int> components(cMax);
int cur_time = 1;

void DFS(int v, bool reverse, int component) {
  visited[v] = true;
  if (reverse) {
    components[v] = component;
  }
  for (auto u : reverse ? reverse_g[v] : g[v]) {
    if (visited[u]) {
      continue;
    }
    DFS(u, reverse, component);
  }
  tout[v] = ++cur_time;
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
    reverse_g[v].push_back(u);
  }
  for (int v = 1; v <= n; ++v) {
    if (visited[v]) {
      continue;
    }
    DFS(v, false, 0);
  }

  std::vector<int> order(n);
  std::iota(order.begin(), order.end(), 1);
  std::sort(order.begin(), order.end(),
            [](int u, int v) { return tout[u] > tout[v]; });
  visited.assign(cMax, false);
  int cur_component = 0;
  for (auto v : order) {
    if (visited[v]) {
      continue;
    }
    DFS(v, true, ++cur_component);
  }
  std::cout << cur_component << '\n';
  for (int v = 1; v <= n; ++v) {
    std::cout << components[v] << ' ';
  }
}