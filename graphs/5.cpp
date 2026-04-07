#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int n;
int m;
int timer = 0;
std::vector<int> tin;
std::vector<bool> visited;
std::vector<int> ret;
std::vector<int> ans;
std::vector<std::vector<int>> g;
std::map<std::pair<int, int>, int> a;

void DFS(int v, int p = 0) {
  tin[v] = ++timer;
  visited[v] = true;
  ret[v] = tin[v];
  for (auto to : g[v]) {
    if (to == p) {
      continue;
    }
    if (visited[to]) {
      ret[v] = std::min(ret[v], tin[to]);
      continue;
    }
    DFS(to, v);
    ret[v] = std::min(ret[v], ret[to]);
    if (ret[to] == tin[to]) {
      auto edge = std::make_pair(v, to);
      if (a[edge] != -1) {
        ans.push_back(a[edge]);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  timer = 0;
  std::cin >> n >> m;
  tin.assign(n + 1, 0);
  visited.assign(n + 1, false);
  ret.assign(n + 1, 0);
  g.resize(n + 1);
  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    if (u == v) {
      continue;
    }
    g[u].push_back(v);
    g[v].push_back(u);
    auto edge1 = std::make_pair(u, v);
    auto edge2 = std::make_pair(v, u);
    if (a.find(edge1) == a.end()) {
      a[edge1] = a[edge2] = i;
    } else {
      a[edge1] = a[edge2] = -1;
    }
  }
  for (int u = 1; u <= n; ++u) {
    if (visited[u]) {
      continue;
    }
    DFS(u);
  }
  std::cout << ans.size() << '\n';
  std::sort(ans.begin(), ans.end());
  for (auto edge : ans) {
    std::cout << edge << ' ';
  }
}