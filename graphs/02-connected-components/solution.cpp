#include <iostream>
#include <vector>

const int cMax = 2 * 1e5 + 1;

std::vector<std::vector<int>> graph(cMax);
std::vector<bool> visited(cMax, false);
std::vector<std::vector<int>> components(cMax);

void Dfs(int vertex, int component) {
  visited[vertex] = true;
  components[component].push_back(vertex);
  for (int next : graph[vertex]) {
    if (!visited[next]) {
      Dfs(next, component);
    }
  }
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
    graph[to].push_back(from);
  }

  int component_count = 0;
  for (int vertex = 1; vertex <= vertices; ++vertex) {
    if (!visited[vertex]) {
      Dfs(vertex, ++component_count);
    }
  }

  std::cout << component_count << '\n';
  for (int i = 1; i <= component_count; ++i) {
    std::cout << components[i].size() << '\n';
    for (int vertex : components[i]) {
      std::cout << vertex << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
