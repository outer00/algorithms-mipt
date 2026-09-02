#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<bool> visited;

void Dfs(int v) {
  visited[v] = true;
  for (int u : graph[v]) {
    if (!visited[u]) {
      Dfs(u);
    }
  }
}

int main() {
  int left_size;
  int right_size;
  std::cin >> left_size >> right_size;

  std::vector<std::pair<int, int>> edges;
  graph.resize(left_size + right_size + 1);
  visited.resize(left_size + right_size + 1);

  for (int v = 1; v <= left_size; ++v) {
    int degree;
    std::cin >> degree;
    for (int j = 0; j < degree; ++j) {
      int u;
      std::cin >> u;
      edges.emplace_back(v, u);
    }
  }

  std::vector<int> match(left_size + 1);
  for (int v = 1; v <= left_size; ++v) {
    std::cin >> match[v];
  }

  for (const auto& [v, u] : edges) {
    if (match[v] != u) {
      graph[v].push_back(left_size + u);
    } else {
      graph[left_size + u].push_back(v);
    }
  }

  for (int v = 1; v <= left_size; ++v) {
    if (match[v] == 0) {
      Dfs(v);
    }
  }

  std::vector<int> left_cover;
  std::vector<int> right_cover;
  for (int v = 1; v <= left_size; ++v) {
    if (!visited[v]) {
      left_cover.push_back(v);
    }
  }
  for (int v = left_size + 1; v <= left_size + right_size; ++v) {
    if (visited[v]) {
      right_cover.push_back(v - left_size);
    }
  }

  std::cout << left_cover.size() + right_cover.size() << "\n";
  std::cout << left_cover.size() << ' ';
  for (int v : left_cover) {
    std::cout << v << ' ';
  }
  std::cout << "\n" << right_cover.size() << ' ';
  for (int v : right_cover) {
    std::cout << v << ' ';
  }
  return 0;
}
