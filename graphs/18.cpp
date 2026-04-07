#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

class DSU {
  std::vector<int> parent_;
  std::vector<int> size_;
  int Get(int v) {
    if (parent_[v] == -1 || parent_[v] == v) {
      return v;
    }
    return Get(parent_[v]);
  }

public:
  explicit DSU(int n) : parent_(n + 1, -1), size_(n + 1, 1) {}

  void Unite(int first, int second) {
    first = Get(first);
    second = Get(second);
    if (first == second) {
      return;
    }
    if (size_[first] < size_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    size_[first] = std::max(size_[second] + 1, size_[first]);
  }
  bool Ask(int first, int second) { return Get(first) == Get(second); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  int m;
  int k;
  int temp;
  std::cin >> n >> m >> k;
  DSU graph(n);
  int cnt = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> temp >> temp;
  }
  std::vector<std::tuple<bool, int, int>> cmds;
  int first;
  int second;
  std::string tempp;
  for (int i = 0; i < k; ++i) {
    std::cin >> tempp >> first >> second;
    if (tempp == "ask") {
      ++cnt;
      cmds.emplace_back(true, first, second);
    } else {
      cmds.emplace_back(false, first, second);
    }
  }
  std::reverse(cmds.begin(), cmds.end());
  std::vector<bool> ans(cnt);
  for (const auto& command : cmds) {
    bool type;
    int u;
    int v;
    std::tie(type, u, v) = command;
    if (type) {
      ans[--cnt] = graph.Ask(u, v);
    } else {
      graph.Unite(u, v);
    }
  }
  for (const auto& an : ans) {
    std::cout << (an ? "YES\n" : "NO\n");
  }
}