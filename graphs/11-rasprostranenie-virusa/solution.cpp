#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  long long vertices;
  long long edges;
  long long viruses;
  std::cin >> vertices >> edges >> viruses;

  std::vector<long long> infected(viruses);
  for (long long& vertex : infected) {
    std::cin >> vertex;
  }

  std::vector<std::vector<std::pair<long long, long long>>> graph(vertices + 1);
  for (long long i = 0; i < edges; ++i) {
    long long from;
    long long to;
    long long length;
    std::cin >> from >> to >> length;
    graph[from].emplace_back(to, length);
    graph[to].emplace_back(from, length);
  }

  long long start;
  long long finish;
  std::cin >> start >> finish;

  std::vector<long long> distances(vertices + 1, LLONG_MAX);
  distances[finish] = 0;

  std::set<std::pair<long long, long long>> queue;
  queue.emplace(0, finish);

  while (!queue.empty()) {
    auto [distance, vertex] = *queue.begin();
    queue.erase(queue.begin());
    if (distance > distances[vertex]) {
      continue;
    }
    for (const auto& [next, weight] : graph[vertex]) {
      if (distance + weight < distances[next]) {
        distances[next] = distance + weight;
        queue.emplace(distances[next], next);
      }
    }
  }

  long long nearest_virus = LLONG_MAX;
  for (long long vertex : infected) {
    nearest_virus = std::min(nearest_virus, distances[vertex]);
  }

  if (distances[start] >= nearest_virus) {
    std::cout << -1;
  } else {
    std::cout << distances[start];
  }
  return 0;
}
