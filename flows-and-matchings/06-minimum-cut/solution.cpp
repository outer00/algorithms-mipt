#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

struct PairHash {
  std::size_t operator()(const std::pair<int, int>& p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

int vertices;

int PushFlow(int from, int to, int min_capacity, std::vector<bool>& visited,
             std::vector<std::vector<int>>& capacity) {
  if (from == to) {
    return min_capacity;
  }
  visited[from] = true;
  for (int next = 1; next <= vertices; ++next) {
    if (capacity[from][next] == 0 || visited[next]) {
      continue;
    }
    int flow = PushFlow(next, to, std::min(capacity[from][next], min_capacity),
                        visited, capacity);
    if (flow > 0) {
      capacity[from][next] -= flow;
      capacity[next][from] += flow;
      return flow;
    }
  }
  return 0;
}

void MarkReachable(int from, std::vector<bool>& visited,
                   std::vector<std::vector<int>>& capacity) {
  visited[from] = true;
  for (int next = 1; next <= vertices; ++next) {
    if (!visited[next] && capacity[from][next] > 0) {
      MarkReachable(next, visited, capacity);
    }
  }
}

int main() {
  int edges;
  std::cin >> vertices >> edges;

  std::vector<std::vector<int>> capacity(vertices + 1,
                                         std::vector<int>(vertices + 1, 0));
  std::unordered_map<std::pair<int, int>, int, PairHash> edge_id;
  std::vector<bool> visited(vertices + 1, false);

  for (int i = 1; i <= edges; ++i) {
    int u;
    int v;
    int c;
    std::cin >> u >> v >> c;
    edge_id[{u, v}] = edge_id[{v, u}] = i;
    capacity[u][v] = c;
    capacity[v][u] = c;
  }

  int min_cut = 0;
  while (int flow = PushFlow(1, vertices, INT_MAX, visited, capacity)) {
    min_cut += flow;
    visited.assign(vertices + 1, false);
  }

  MarkReachable(1, visited, capacity);

  std::set<int> answer;
  for (const auto& [ends, id] : edge_id) {
    if (visited[ends.first] != visited[ends.second]) {
      answer.insert(id);
    }
  }

  std::cout << answer.size() << ' ' << min_cut << '\n';
  for (int id : answer) {
    std::cout << id << ' ';
  }
  return 0;
}
