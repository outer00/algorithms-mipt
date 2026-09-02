#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

int vertices;
int edges;
int timer = 0;

std::vector<int> enter_time;
std::vector<bool> visited;
std::vector<int> low;
std::vector<int> answer;
std::vector<std::vector<int>> graph;
std::map<std::pair<int, int>, int> edge_id;

void Dfs(int vertex, int parent = 0) {
  enter_time[vertex] = ++timer;
  visited[vertex] = true;
  low[vertex] = enter_time[vertex];

  for (int next : graph[vertex]) {
    if (next == parent) {
      continue;
    }
    if (visited[next]) {
      low[vertex] = std::min(low[vertex], enter_time[next]);
      continue;
    }
    Dfs(next, vertex);
    low[vertex] = std::min(low[vertex], low[next]);
    if (low[next] == enter_time[next]) {
      int id = edge_id[{vertex, next}];
      if (id != -1) {
        answer.push_back(id);
      }
    }
  }
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
    if (edge_id.find({from, to}) == edge_id.end()) {
      edge_id[{from, to}] = edge_id[{to, from}] = i;
    } else {
      edge_id[{from, to}] = edge_id[{to, from}] = -1;
    }
  }

  for (int vertex = 1; vertex <= vertices; ++vertex) {
    if (!visited[vertex]) {
      Dfs(vertex);
    }
  }

  std::cout << answer.size() << '\n';
  std::sort(answer.begin(), answer.end());
  for (int id : answer) {
    std::cout << id << ' ';
  }
  return 0;
}
