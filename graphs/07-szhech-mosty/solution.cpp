#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

int timer = 0;
const int cMax = 5e3 + 1;

std::vector<int> enter_time(cMax);
std::vector<bool> visited(cMax, false);
std::vector<int> low(cMax);
std::vector<int> leaf_bridges;
std::vector<std::vector<int>> graph(cMax);
std::map<std::pair<int, int>, int> edge_id;

bool Dfs(int vertex, int parent = 0) {
  enter_time[vertex] = ++timer;
  visited[vertex] = true;
  low[vertex] = enter_time[vertex];

  bool subtree_has_bridge = false;
  for (int next : graph[vertex]) {
    if (next == parent) {
      continue;
    }
    if (visited[next]) {
      low[vertex] = std::min(low[vertex], enter_time[next]);
      continue;
    }
    bool child_has_bridge = Dfs(next, vertex);
    subtree_has_bridge |= child_has_bridge;
    low[vertex] = std::min(low[vertex], low[next]);
    if (low[next] == enter_time[next] && !child_has_bridge) {
      leaf_bridges.push_back(edge_id[{vertex, next}]);
      subtree_has_bridge = true;
    }
  }
  return subtree_has_bridge;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertices;
  int edges;
  std::cin >> vertices >> edges;

  for (int i = 1; i <= edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    graph[from].push_back(to);
    graph[to].push_back(from);
    edge_id[{from, to}] = edge_id[{to, from}] = i;
  }

  Dfs(1);

  int leaves = leaf_bridges.size() + static_cast<int>(graph[1].size() == 1);
  std::cout << (leaves + 1) / 2 << '\n';
  return 0;
}
