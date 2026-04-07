#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

enum Color { WHITE, GREY, BLACK };

const int cMax = 1e5 + 1;
std::vector<std::vector<int>> g(cMax);
std::vector<int> visited(cMax, WHITE);
std::vector<int> tout(cMax);
int cur_time = 1;

bool DFS(int v) {
  visited[v] = GREY;
  for (auto u : g[v]) {
    if (visited[u] == GREY) {
      return false;
    }
    if (visited[u] == BLACK) {
      continue;
    }
    if (!DFS(u)) {
      return false;
    }
  }
  tout[v] = ++cur_time;
  visited[v] = BLACK;
  return true;
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
  }
  for (int v = 1; v <= n; ++v) {
    if (visited[v] == BLACK) {
      continue;
    }
    if (!DFS(v)) {
      std::cout << -1;
      return 0;
    }
  }

  std::vector<int> ans(n);
  std::iota(ans.begin(), ans.end(), 1);
  std::sort(ans.begin(), ans.end(),
            [](int u, int v) { return tout[u] > tout[v]; });
  for (auto u : ans) {
    std::cout << u << ' ';
  }
}