#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

enum Color { WHITE, GREY, BLACK };

const int cMax = 1e5 + 1;

std::vector<std::vector<int>> graph(cMax);
std::vector<int> color(cMax, WHITE);
std::vector<int> exit_time(cMax);
int timer = 1;

bool Dfs(int vertex) {
  color[vertex] = GREY;
  for (int next : graph[vertex]) {
    if (color[next] == GREY) {
      return false;
    }
    if (color[next] == BLACK) {
      continue;
    }
    if (!Dfs(next)) {
      return false;
    }
  }
  exit_time[vertex] = ++timer;
  color[vertex] = BLACK;
  return true;
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
  }

  for (int vertex = 1; vertex <= vertices; ++vertex) {
    if (color[vertex] == BLACK) {
      continue;
    }
    if (!Dfs(vertex)) {
      std::cout << -1;
      return 0;
    }
  }

  std::vector<int> order(vertices);
  std::iota(order.begin(), order.end(), 1);
  std::sort(order.begin(), order.end(),
            [](int lhs, int rhs) { return exit_time[lhs] > exit_time[rhs]; });

  for (int vertex : order) {
    std::cout << vertex << ' ';
  }
  return 0;
}
