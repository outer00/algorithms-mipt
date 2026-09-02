#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

constexpr long long kInf = LLONG_MAX;

struct Edge {
  int from;
  int to;
  long long cost;
  long long capacity;
  long long flow;
};

std::vector<Edge> ReadEdges(int edge_count) {
  std::vector<Edge> edges;
  edges.reserve(2 * edge_count);
  for (int i = 0; i < edge_count; ++i) {
    int from;
    int to;
    long long capacity;
    long long cost;
    std::cin >> from >> to >> capacity >> cost;
    edges.push_back({from, to, cost, capacity, 0});
    edges.push_back({to, from, -cost, 0, 0});
  }
  return edges;
}

long long MinCostMaxFlow(std::vector<Edge>& edges, int vertices) {
  long long total_cost = 0;
  while (true) {
    std::vector<long long> dist(vertices + 1, kInf);
    std::vector<int> prev_edge(vertices + 1, -1);
    dist[1] = 0;

    for (int step = 0; step < vertices - 1; ++step) {
      for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        const Edge& edge = edges[i];
        if (dist[edge.from] != kInf && edge.flow < edge.capacity &&
            dist[edge.from] + edge.cost < dist[edge.to]) {
          dist[edge.to] = dist[edge.from] + edge.cost;
          prev_edge[edge.to] = i;
        }
      }
    }

    if (dist[vertices] == kInf) {
      return total_cost;
    }

    long long push = kInf;
    for (int i = prev_edge[vertices]; i != -1; i = prev_edge[edges[i].from]) {
      push = std::min(push, edges[i].capacity - edges[i].flow);
    }
    for (int i = prev_edge[vertices]; i != -1; i = prev_edge[edges[i].from]) {
      edges[i].flow += push;
      edges[i ^ 1].flow -= push;
      total_cost += push * edges[i].cost;
    }
  }
}

int main() {
  int vertices;
  int edge_count;
  std::cin >> vertices >> edge_count;

  std::vector<Edge> edges = ReadEdges(edge_count);
  std::cout << MinCostMaxFlow(edges, vertices);
  return 0;
}
