#include <iostream>
#include <vector>

const int cUnreachable = 30000;

struct Edge {
  int from;
  int to;
  int weight;
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void FordBellman(int vertices, const std::vector<Edge>& edges) {
  std::vector<int> distances(vertices, cUnreachable);
  distances[0] = 0;

  for (int step = 0; step + 1 < vertices; ++step) {
    for (const Edge& edge : edges) {
      if (distances[edge.from] != cUnreachable &&
          distances[edge.from] + edge.weight < distances[edge.to]) {
        distances[edge.to] = distances[edge.from] + edge.weight;
      }
    }
  }

  for (int distance : distances) {
    std::cout << distance << ' ';
  }
}

int main() {
  OptimizeIO();

  int vertices;
  int edge_count;
  std::cin >> vertices >> edge_count;

  std::vector<Edge> edges(edge_count);
  for (Edge& edge : edges) {
    std::cin >> edge.from >> edge.to >> edge.weight;
    --edge.from;
    --edge.to;
  }

  FordBellman(vertices, edges);
  return 0;
}
