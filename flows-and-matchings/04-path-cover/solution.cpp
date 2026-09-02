#include <iostream>
#include <vector>

struct BipartiteMatching {
  std::vector<std::vector<int>> adj;
  std::vector<int> match;
  std::vector<bool> visited;

  explicit BipartiteMatching(int size)
      : adj(size + 1), match(size + 1, -1), visited(size + 1, false) {}

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
  int vertices;
  int edges;
  std::cin >> vertices >> edges;

  BipartiteMatching matching(vertices);
  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    matching.adj[from].push_back(to);
  }

  for (int v = 1; v <= vertices; ++v) {
    matching.Augment(v);
  }

  int answer = 0;
  for (int v = 1; v <= vertices; ++v) {
    if (matching.match[v] == -1) {
      ++answer;
    }
  }

  std::cout << answer;
  return 0;
}
