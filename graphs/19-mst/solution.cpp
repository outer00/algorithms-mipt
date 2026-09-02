#include <climits>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

struct Edge {
  int weight;
  int to;
  Edge(int weight, int to) : weight(weight), to(to) {}
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertices;
  int edges;
  std::cin >> vertices >> edges;

  std::vector<std::vector<Edge>> graph(vertices + 1);
  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    int weight;
    std::cin >> from >> to >> weight;
    graph[from].emplace_back(weight, to);
    graph[to].emplace_back(weight, from);
  }

  std::vector<int> min_edge(vertices + 1, INT_MAX);
  std::vector<bool> visited(vertices + 1, false);
  std::set<std::pair<int, int>> queue;

  const int start = 1;
  min_edge[start] = 0;
  queue.emplace(0, start);

  int answer = 0;
  while (!queue.empty()) {
    auto [weight, vertex] = *queue.begin();
    queue.erase(queue.begin());
    if (visited[vertex]) {
      continue;
    }
    visited[vertex] = true;
    answer += weight;

    for (const Edge& edge : graph[vertex]) {
      if (!visited[edge.to] && edge.weight < min_edge[edge.to]) {
        min_edge[edge.to] = edge.weight;
        queue.emplace(edge.weight, edge.to);
      }
    }
  }

  std::cout << answer << '\n';
  return 0;
}
