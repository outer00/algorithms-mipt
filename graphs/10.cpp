#include <iostream>
#include <queue>
#include <set>
#include <vector>

struct Edge {
  int to;
  int weight;
};

void Dijkstra(const std::vector<std::vector<Edge>>& graph,
              std::vector<int>& distances, int start) {
  std::set<std::pair<int, int>> pq;
  pq.emplace(0, start);
  distances[start] = 0;
  int from;
  int dist;
  int to;
  int weight;
  while (!pq.empty()) {
    auto aaa = *(pq.begin());
    from = aaa.second;
    dist = aaa.first;
    pq.erase(pq.begin());
    if (dist > distances[from]) {
      continue;
    }
    for (const auto& edge : graph[from]) {
      to = edge.to;
      weight = edge.weight;
      if (dist + weight < distances[to]) {
        distances[to] = dist + weight;
        pq.emplace(distances[to], to);
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
  const int cKIntMax = 2009000999;
  int map_count;
  std::cin >> map_count;
  int num;
  int mnum;
  int from;
  int to;
  int weight;
  int start;
  for (int k = 0; k < map_count; ++k) {
    std::cin >> num >> mnum;
    std::vector<std::vector<Edge>> graph(num);
    for (int i = 0; i < mnum; ++i) {
      std::cin >> from >> to >> weight;
      graph[from].emplace_back(to, weight);
      graph[to].emplace_back(from, weight);
    }
    std::cin >> start;
    std::vector<int> distances(num, cKIntMax);
    Dijkstra(graph, distances, start);
    for (int i = 0; i < num; ++i) {
      if (distances[i] == cKIntMax) {
        std::cout << cKIntMax << " ";
      } else {
        std::cout << distances[i] << " ";
      }
    }
    std::cout << '\n';
  }
  return 0;
}
