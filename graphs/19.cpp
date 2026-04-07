#include <climits>
#include <iostream>
#include <set>
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
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n + 1);
  int first;
  int second;
  int weight;
  for (int i = 0; i < m; ++i) {
    std::cin >> first >> second >> weight;
    graph[first].emplace_back(weight, second);
    graph[second].emplace_back(weight, first);
  }
  int start = 1;
  std::vector<int> dist(n + 1, INT_MAX);
  std::vector<bool> visited(n + 1, false);
  std::set<std::pair<int, int>> set;
  dist[start] = 0;
  set.emplace(0, start);
  int ans = 0;

  while (!set.empty()) {
    auto val = *(set.begin());
    weight = val.first;
    first = val.second;
    set.erase(set.begin());
    if (visited[first]) {
      continue;
    }
    visited[first] = true;
    ans += weight;
    for (const auto& edge : graph[first]) {
      if (!visited[edge.to] && edge.weight < dist[edge.to]) {
        dist[edge.to] = edge.weight;
        set.emplace(dist[edge.to], edge.to);
      }
    }
  }
  std::cout << ans << '\n';
}