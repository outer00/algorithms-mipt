#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  const int cNoEdge = 1e5;

  int vertices;
  std::cin >> vertices;

  std::vector<std::tuple<int, int, int>> edges;
  for (int i = 1; i <= vertices; ++i) {
    for (int j = 1; j <= vertices; ++j) {
      int weight;
      std::cin >> weight;
      if (weight != cNoEdge) {
        edges.emplace_back(i, j, weight);
      }
    }
  }

  std::vector<int> distances(vertices + 1, 0);
  std::vector<int> parent(vertices + 1, -1);

  int relaxed = INT_MAX;
  for (int step = 0; step < vertices; ++step) {
    relaxed = INT_MAX;
    for (const auto& [from, to, weight] : edges) {
      if (distances[from] + weight < distances[to]) {
        distances[to] = distances[from] + weight;
        parent[to] = from;
        relaxed = to;
      }
    }
  }

  if (relaxed == INT_MAX) {
    std::cout << "NO";
    return 0;
  }

  std::cout << "YES\n";

  for (int i = 0; i < vertices; ++i) {
    relaxed = parent[relaxed];
  }

  std::vector<int> cycle;
  int current = relaxed;
  do {
    cycle.push_back(current);
    current = parent[current];
  } while (current != relaxed);
  cycle.push_back(relaxed);

  std::cout << cycle.size() << '\n';
  for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
    std::cout << *it << ' ';
  }
  return 0;
}
