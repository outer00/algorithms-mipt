#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

constexpr size_t cMax = 1e6 + 1;

std::array<bool, cMax> visited;
std::array<bool, cMax> odd_vertex;
std::array<bool, cMax> edge_value;
std::vector<std::vector<std::pair<int, int>>> graph(cMax);

bool Dfs(int vertex, int parent = -1) {
  visited[vertex] = true;
  bool needs_one = odd_vertex[vertex];
  for (const auto& [next, id] : graph[vertex]) {
    if (next == parent || visited[next]) {
      continue;
    }
    bool child_needs_one = Dfs(next, vertex);
    needs_one ^= child_needs_one;
    if (child_needs_one) {
      edge_value[id] = true;
    }
  }
  return needs_one;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int tests;
  std::cin >> tests;

  int prev_vertices = 0;
  while (tests-- != 0) {
    int vertices;
    int edges;
    std::cin >> vertices >> edges;

    std::fill(visited.begin(), visited.begin() + vertices + 1, false);
    std::fill(odd_vertex.begin(), odd_vertex.begin() + vertices + 1, false);
    std::fill(edge_value.begin(), edge_value.begin() + edges + 1, false);
    for (int i = 0; i <= std::min(vertices, prev_vertices); ++i) {
      graph[i].clear();
    }
    prev_vertices = std::max(vertices, prev_vertices);

    for (int i = 1; i <= edges; ++i) {
      int from;
      int to;
      std::cin >> from >> to;
      graph[from].emplace_back(to, i);
      graph[to].emplace_back(from, i);
    }

    for (int i = 1; i <= vertices; ++i) {
      char digit;
      std::cin >> digit;
      odd_vertex[i] = digit == '1';
    }

    bool impossible = false;
    for (int vertex = 1; vertex <= vertices; ++vertex) {
      if (!visited[vertex]) {
        impossible |= Dfs(vertex);
      }
    }

    if (impossible) {
      std::cout << "-1\n";
      continue;
    }

    std::string answer(edges, '0');
    for (int i = 1; i <= edges; ++i) {
      if (edge_value[i]) {
        answer[i - 1] = '1';
      }
    }
    std::cout << answer << '\n';
  }
  return 0;
}
