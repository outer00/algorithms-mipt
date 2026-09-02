#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int vertices;
int edges;
int timer = 0;

std::vector<int> enter_time;
std::vector<bool> visited;
std::vector<int> low;
std::vector<std::vector<int>> graph;
std::set<int> answer;

int Dfs(int vertex, int parent = 0) {
  enter_time[vertex] = ++timer;
  visited[vertex] = true;
  low[vertex] = enter_time[vertex];

  int children = 0;
  bool is_cut_point = false;
  for (int next : graph[vertex]) {
    if (next == parent) {
      continue;
    }
    if (visited[next]) {
      low[vertex] = std::min(low[vertex], enter_time[next]);
      continue;
    }
    ++children;
    Dfs(next, vertex);
    low[vertex] = std::min(low[vertex], low[next]);
    if (parent != 0 && low[next] >= enter_time[vertex]) {
      is_cut_point = true;
    }
  }

  if (is_cut_point) {
    answer.insert(vertex);
  }
  return children;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> vertices >> edges;
  enter_time.assign(vertices + 1, 0);
  visited.assign(vertices + 1, false);
  low.assign(vertices + 1, 0);
  graph.resize(vertices + 1);

  for (int i = 1; i <= edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    if (from == to) {
      continue;
    }
    graph[from].push_back(to);
    graph[to].push_back(from);
  }

  for (int vertex = 1; vertex <= vertices; ++vertex) {
    if (visited[vertex]) {
      continue;
    }
    if (Dfs(vertex) > 1) {
      answer.insert(vertex);
    }
  }

  std::cout << answer.size() << '\n';
  for (int vertex : answer) {
    std::cout << vertex << ' ';
  }
  return 0;
}
