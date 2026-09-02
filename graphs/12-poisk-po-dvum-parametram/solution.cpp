#include <climits>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

int main() {
  int vertices;
  int edges;
  int time_limit;
  std::cin >> vertices >> edges >> time_limit;

  std::vector<std::vector<std::tuple<int, int, int>>> graph(vertices + 1);
  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    int cost;
    int time;
    std::cin >> from >> to >> cost >> time;
    --from;
    --to;
    graph[from].emplace_back(to, cost, time);
    graph[to].emplace_back(from, cost, time);
  }

  int states = (time_limit + 1) * (vertices + 1);
  std::vector<int> min_time(vertices + 1, INT_MAX);
  std::vector<int> cost(states, INT_MAX);
  std::vector<int> parent(states, -1);

  std::set<std::pair<int, int>> queue;
  queue.emplace(0, vertices - 1);
  min_time[vertices - 1] = 0;

  while (!queue.empty()) {
    auto [time, vertex] = *queue.begin();
    queue.erase(queue.begin());
    if (time > min_time[vertex]) {
      continue;
    }
    min_time[vertex] = time;
    for (const auto& [next, edge_cost, edge_time] : graph[vertex]) {
      if (time + edge_time < min_time[next]) {
        queue.emplace(time + edge_time, next);
      }
    }
  }

  queue.emplace(0, 0);
  cost[0] = 0;

  while (!queue.empty()) {
    auto [current_cost, state] = *queue.begin();
    queue.erase(queue.begin());
    if (current_cost > cost[state]) {
      continue;
    }
    int vertex = state / (time_limit + 1);
    int spent = state % (time_limit + 1);
    for (const auto& [next, edge_cost, edge_time] : graph[vertex]) {
      if (spent + edge_time + min_time[next] > time_limit) {
        continue;
      }
      int next_state = next * (time_limit + 1) + spent + edge_time;
      if (current_cost + edge_cost < cost[next_state]) {
        cost[next_state] = current_cost + edge_cost;
        parent[next_state] = state;
        queue.emplace(cost[next_state], next_state);
      }
    }
  }

  int best_state = -1;
  int min_cost = INT_MAX;
  for (int spent = 0; spent <= time_limit; ++spent) {
    int state = (vertices - 1) * (time_limit + 1) + spent;
    if (cost[state] < min_cost) {
      min_cost = cost[state];
      best_state = state;
    }
  }

  if (min_cost == INT_MAX) {
    std::cout << "-1\n";
    return 0;
  }

  std::cout << min_cost << "\n";

  std::vector<int> path;
  path.push_back(best_state / (time_limit + 1) + 1);
  while (parent[best_state] != -1) {
    best_state = parent[best_state];
    path.push_back(best_state / (time_limit + 1) + 1);
  }

  std::cout << path.size() << "\n";
  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    std::cout << *it << " ";
  }
  return 0;
}
