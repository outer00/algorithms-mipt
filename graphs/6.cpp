#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int n;
int m;
int timer = 0;
std::vector<int> tin;
std::vector<bool> visited;
std::vector<int> ret;
std::vector<std::vector<int>> g;
std::set<int> ans;

int DFS(int v, int p = 0) {
  tin[v] = ++timer;
  visited[v] = true;
  ret[v] = tin[v];
  int cnt = 0;
  bool flag = false;
  for (auto to : g[v]) {
    if (to == p) {
      continue;
    }
    if (visited[to]) {
      ret[v] = std::min(ret[v], tin[to]);
      continue;
    }
    ++cnt;
    DFS(to, v);
    ret[v] = std::min(ret[v], ret[to]);
    if (p != 0 && ret[to] >= tin[v]) {
      flag = true;
    }
  }
  if (flag) {
    ans.insert(v);
  }
  return cnt;
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
  }
  for (int u = 1; u <= n; ++u) {
    if (visited[u]) {
      continue;
    }
    if (DFS(u) > 1) {
      ans.insert(u);
    }
  }
  std::cout << ans.size() << '\n';
  for (auto edge : ans) {
    std::cout << edge << ' ';
  }
}