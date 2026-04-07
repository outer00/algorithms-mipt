#include <climits>
#include <iostream>
#include <set>
#include <vector>

int n;
int cnt = 0;
const int cMax = 1e6 + 1;
std::vector<std::vector<std::pair<int, int>>> g(cMax);
std::vector<std::pair<int, int>> coefficients(cMax);
std::vector<bool> visited(cMax, false);
std::vector<bool> permutations(cMax, false);
std::vector<int> ans(cMax, 0);

void DFS(int v) {
  visited[v] = true;
  for (const auto& nxt : g[v]) {
    if (visited[nxt.first]) {
      continue;
    }
    coefficients[nxt.first].first = -coefficients[v].first;
    coefficients[nxt.first].second = nxt.second - coefficients[v].second;
    DFS(nxt.first);
  }
}

bool CheckDFS(int u, int val) {
  visited[u] = true;
  if (permutations[val] || val < 1 || val > n) {
    return false;
  }
  permutations[val] = true;

  ans[u] = val;
  for (const auto& nxt : g[u]) {
    if (visited[nxt.first]) {
      if (val + ans[nxt.first] != nxt.second) {
        return false;
      }
      continue;
    }
    if (!CheckDFS(nxt.first, nxt.second - val)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int m;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int s;
    std::cin >> u >> v >> s;
    g[u].emplace_back(v, s);
    g[v].emplace_back(u, s);
  }

  coefficients[1] = std::make_pair(1, 0);
  DFS(1);
  int positive = 0;
  int negative = INT_MAX;
  for (int v = 1; v <= n; ++v) {
    coefficients[v].first == 1
        ? positive = std::min(positive, coefficients[v].second)
        : negative = std::min(negative, coefficients[v].second);
  }

  int x1 = 1 - positive;
  int x2 = negative - 1;
  visited.assign(cMax, false);
  if (CheckDFS(1, x1)) {
    for (int v = 1; v <= n; ++v) {
      std::cout << ans[v] << ' ';
    }
    return 0;
  }
  visited.assign(cMax, false);
  ans.assign(cMax, 0);
  permutations.assign(cMax, false);
  CheckDFS(1, x2);
  for (int v = 1; v <= n; ++v) {
    std::cout << ans[v] << ' ';
  }
}