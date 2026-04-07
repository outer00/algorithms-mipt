#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int timer = 0;
const int cMax = 5e3 + 1;
std::vector<int> tin(cMax);
std::vector<bool> visited(cMax, false);
std::vector<int> ret(cMax);
std::vector<int> ans;
std::vector<std::vector<int>> g(cMax);
std::map<std::pair<int, int>, int> a;

bool DFS(int v, int p = 0) {
  tin[v] = ++timer;
  visited[v] = true;
  ret[v] = tin[v];
  bool flag2 = false;
  for (auto to : g[v]) {
    if (to == p) {
      continue;
    }
    if (visited[to]) {
      ret[v] = std::min(ret[v], tin[to]);
      continue;
    }
    bool flag = DFS(to, v);
    flag2 |= flag;
    ret[v] = std::min(ret[v], ret[to]);
    if (ret[to] == tin[to]) {
      if (flag) {
        continue;
      }
      auto edge = std::make_pair(v, to);
      ans.push_back(a[edge]);
      flag2 = true;
    }
  }
  return flag2;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  int m;
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u;
    int v;
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
    auto edge1 = std::make_pair(u, v);
    auto edge2 = std::make_pair(v, u);
    a[edge1] = a[edge2] = i;
  }

  DFS(1);
  std::cout << (ans.size() + 1 + static_cast<int>(g[1].size() == 1)) / 2
            << '\n';
}