#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct Edge {
  int to;
  int weight;
};

void Dijkstra(const std::vector<std::vector<Edge>>& graph,
              std::vector<int>& distances, int start) {
  std::set<std::pair<int, int>> queue;
  queue.emplace(0, start);
  distances[start] = 0;

  while (!queue.empty()) {
    auto [distance, from] = *queue.begin();
    queue.erase(queue.begin());
    if (distance > distances[from]) {
      continue;
    }
    for (const Edge& edge : graph[from]) {
      if (distance + edge.weight < distances[edge.to]) {
        distances[edge.to] = distance + edge.weight;
        queue.emplace(distances[edge.to], edge.to);
      }
    }
  }
}

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  const int cUnreachable = 2009000999;

  int tests;
  std::cin >> tests;
  for (int test = 0; test < tests; ++test) {
    int vertices;
    int edges;
    std::cin >> vertices >> edges;

    std::vector<std::vector<Edge>> graph(vertices);
    for (int i = 0; i < edges; ++i) {
      int from;
      int to;
      int weight;
      std::cin >> from >> to >> weight;
      graph[from].emplace_back(to, weight);
      graph[to].emplace_back(from, weight);
    }

    int start;
    std::cin >> start;

    std::vector<int> distances(vertices, cUnreachable);
    Dijkstra(graph, distances, start);

    for (int distance : distances) {
      std::cout << distance << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
