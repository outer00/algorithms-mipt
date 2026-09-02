#include <iostream>
#include <vector>

struct BipartiteMatching {
  std::vector<std::vector<int>> adj;
  std::vector<int> match;
  std::vector<bool> visited;

  BipartiteMatching(int left_size, int right_size)
      : adj(left_size + 1),
        match(right_size + 1, -1),
        visited(left_size + 1, false) {}

  bool TryKuhn(int v) {
    if (visited[v]) {
      return false;
    }
    visited[v] = true;
    for (int u : adj[v]) {
      if (match[u] == -1 || TryKuhn(match[u])) {
        match[u] = v;
        return true;
      }
    }
    return false;
  }

  void Augment(int v) {
    TryKuhn(v);
    visited.assign(visited.size(), false);
  }
};

int main() {
  int left_size;
  int right_size;
  std::cin >> left_size >> right_size;

  BipartiteMatching matching(left_size, right_size);
  for (int v = 1; v <= left_size; ++v) {
    int u;
    std::cin >> u;
    while (u != 0) {
      matching.adj[v].push_back(u);
      std::cin >> u;
    }
  }

  for (int v = 1; v <= left_size; ++v) {
    matching.Augment(v);
  }

  int answer = 0;
  for (int u = 1; u <= right_size; ++u) {
    if (matching.match[u] != -1) {
      ++answer;
    }
  }

  std::cout << answer << '\n';
  for (int u = 1; u <= right_size; ++u) {
    if (matching.match[u] != -1) {
      std::cout << matching.match[u] << ' ' << u << '\n';
    }
  }
  return 0;
}
