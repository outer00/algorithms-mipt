#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

struct Graph {
  std::vector<std::vector<int>> capacity;
  std::vector<bool> visited;
  int size;

  explicit Graph(int size)
      : capacity(size + 1, std::vector<int>(size + 1)),
        visited(size + 1, false),
        size(size) {}

  int FindAugmentingPath(int from, int to, int min_capacity) {
    if (from == to) {
      return min_capacity;
    }
    visited[from] = true;
    for (int next = 1; next <= size; ++next) {
      if (capacity[from][next] == 0 || visited[next]) {
        continue;
      }
      int flow = FindAugmentingPath(next, to,
                                    std::min(min_capacity, capacity[from][next]));
      if (flow > 0) {
        capacity[from][next] -= flow;
        capacity[next][from] += flow;
        return flow;
      }
    }
    return 0;
  }
};

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;

  Graph graph(vertices);
  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    std::cin >> graph.capacity[from][to];
  }

  int max_flow = 0;
  while (int flow = graph.FindAugmentingPath(1, vertices, INT_MAX)) {
    max_flow += flow;
    graph.visited.assign(vertices + 1, false);
  }

  std::cout << max_flow;
  return 0;
}
