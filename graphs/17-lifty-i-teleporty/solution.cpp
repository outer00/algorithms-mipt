#include <iostream>
#include <set>
#include <utility>
#include <vector>

int main() {
  const int cMaxFloors = 1e6;
  const int cInf = 1e9;

  int floors;
  int up_cost;
  int down_cost;
  int enter_cost;
  int exit_cost;
  int teleports;
  std::cin >> floors >> up_cost >> down_cost >> enter_cost >> exit_cost >>
      teleports;

  std::vector<std::vector<std::pair<int, int>>> graph(cMaxFloors + teleports + 1);
  std::vector<int> dist(cMaxFloors + teleports + 1, cInf);

  std::set<int> used_floors;
  used_floors.insert(1);
  used_floors.insert(floors);

  for (int teleport = 1; teleport <= teleports; ++teleport) {
    int count;
    std::cin >> count;
    for (int j = 0; j < count; ++j) {
      int floor;
      std::cin >> floor;
      graph[cMaxFloors + teleport].emplace_back(floor, exit_cost);
      graph[floor].emplace_back(cMaxFloors + teleport, enter_cost);
      used_floors.insert(floor);
    }
  }

  int previous = *used_floors.begin();
  for (int floor : used_floors) {
    graph[floor].emplace_back(previous, down_cost * (floor - previous));
    graph[previous].emplace_back(floor, up_cost * (floor - previous));
    previous = floor;
  }

  std::set<std::pair<int, int>> queue;
  queue.emplace(0, 1);
  dist[1] = 0;

  while (!queue.empty()) {
    auto [cost, vertex] = *queue.begin();
    queue.erase(queue.begin());
    if (dist[vertex] < cost) {
      continue;
    }
    for (const auto& [next, weight] : graph[vertex]) {
      if (cost + weight < dist[next]) {
        dist[next] = cost + weight;
        queue.emplace(dist[next], next);
      }
    }
  }

  std::cout << dist[floors] << "\n";
  return 0;
}
