#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

const int cMax = 1e5 + 1;

std::vector<std::vector<int>> graph(cMax);
std::vector<std::vector<int>> reversed_graph(cMax);
std::vector<bool> visited(cMax, false);
std::vector<int> exit_time(cMax);
std::vector<int> components(cMax);
int timer = 1;

void Dfs(int vertex, bool reversed, int component) {
  visited[vertex] = true;
  if (reversed) {
    components[vertex] = component;
  }
  for (int next : reversed ? reversed_graph[vertex] : graph[vertex]) {
    if (!visited[next]) {
      Dfs(next, reversed, component);
    }
  }
  exit_time[vertex] = ++timer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertices;
  int edges;
  std::cin >> vertices >> edges;

  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    graph[from].push_back(to);
    reversed_graph[to].push_back(from);
  }

  for (int vertex = 1; vertex <= vertices; ++vertex) {
    if (!visited[vertex]) {
      Dfs(vertex, false, 0);
    }
  }

  std::vector<int> order(vertices);
  std::iota(order.begin(), order.end(), 1);
  std::sort(order.begin(), order.end(),
            [](int lhs, int rhs) { return exit_time[lhs] > exit_time[rhs]; });

  visited.assign(cMax, false);
  int component_count = 0;
  for (int vertex : order) {
    if (!visited[vertex]) {
      Dfs(vertex, true, ++component_count);
    }
  }

  std::cout << component_count << '\n';
  for (int vertex = 1; vertex <= vertices; ++vertex) {
    std::cout << components[vertex] << ' ';
  }
  return 0;
}
