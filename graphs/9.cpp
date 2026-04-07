#include <array>
#include <climits>
#include <iostream>
#include <vector>

constexpr size_t cMax = 1e6 + 1;
std::array<bool, cMax> visited;
std::array<bool, cMax> zeros_v;
std::array<bool, cMax> zeros_e;
std::vector<std::vector<std::pair<int, int>>> g(cMax);

bool DFS(int v, int p = -1) {
  visited[v] = true;
  bool chet = zeros_v[v];
  for (const auto& next : g[v]) {
    if (next.first == p || visited[next.first]) {
      continue;
    }
    bool res = DFS(next.first, v);
    chet ^= static_cast<int>(res);
    if (res) {
      zeros_e[next.second] = true;
    }
  }
  return chet;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  int prev_n = 0;
  while (t-- != 0) {
    int n;
    int m;
    std::cin >> n >> m;
    std::fill(visited.begin(), visited.begin() + n + 1, false);
    std::fill(zeros_v.begin(), zeros_v.begin() + n + 1, false);
    std::fill(zeros_e.begin(), zeros_e.begin() + m + 1, false);
    for (int i = 0; i <= std::min(n, prev_n); ++i) {
      g[i].clear();
    }
    prev_n = std::max(n, prev_n);
    for (int i = 1; i <= m; ++i) {
      int u;
      int v;
      std::cin >> u >> v;
      g[u].emplace_back(v, i);
      g[v].emplace_back(u, i);
    }
    for (int i = 1; i <= n; ++i) {
      char c;
      std::cin >> c;
      zeros_v[i] = (c == '1');
    }
    bool flag = false;
    for (int v = 1; v <= n; ++v) {
      if (!visited[v]) {
        flag |= DFS(v);
      }
    }
    if (flag) {
      std::cout << "-1\n";
    } else {
      std::string ans(m, '0');
      for (int i = 1; i <= m; ++i) {
        if (zeros_e[i]) {
          ans[i - 1] = '1';
        }
      }
      std::cout << ans << '\n';
    }
  }
}