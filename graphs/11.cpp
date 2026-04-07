#include <climits>
#include <iostream>
#include <set>
#include <vector>

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();
  long long num;
  long long mnum;
  long long knum;
  std::cin >> num >> mnum >> knum;
  std::vector<long long> infected(knum);
  std::vector<std::vector<std::pair<long long, long long>>> graph(num + 1);
  std::vector<std::pair<long long, long long>> blocked;

  for (long long i = 0; i < knum; ++i) {
    std::cin >> infected[i];
    for (auto& edge : graph[infected[i]]) {
      blocked.emplace_back(infected[i], edge.first);
      blocked.emplace_back(edge.first, infected[i]);
    }
  }

  long long from;
  long long to;
  long long len;
  for (long long i = 0; i < mnum; ++i) {
    std::cin >> from >> to >> len;
    graph[from].emplace_back(to, len);
    graph[to].emplace_back(from, len);
  }

  long long start;
  long long end;
  std::cin >> start >> end;
  std::vector<long long> distances(num + 1, LLONG_MAX);
  distances[end] = 0;

  std::set<std::pair<long long, long long>> bro;
  bro.emplace(0, end);

  long long current_distance;
  long long current_vertex;

  while (!bro.empty()) {
    auto aaa = *(bro.begin());
    current_distance = aaa.first;
    current_vertex = aaa.second;
    bro.erase(bro.begin());

    if (current_distance > distances[current_vertex]) {
      continue;
    }

    for (auto& edge : graph[current_vertex]) {
      long long neighbor = edge.first;
      long long weight = edge.second;

      bool is_blocked = false;
      for (auto& blocked_edge : blocked) {
        if ((current_vertex == blocked_edge.first &&
             neighbor == blocked_edge.second) ||
            (neighbor == blocked_edge.first &&
             current_vertex == blocked_edge.second)) {
          is_blocked = true;
          break;
        }
      }
      if (is_blocked) {
        continue;
      }

      long long distance = current_distance + weight;
      if (distance < distances[neighbor]) {
        distances[neighbor] = distance;
        bro.emplace(distance, neighbor);
      }
    }
  }
  long long mm = LLONG_MAX;
  for (long long edg : infected) {
    mm = std::min(mm, distances[edg]);
  }
  (distances[start] >= mm) ? std::cout << "-1" : std::cout << distances[start];
  return 0;
}
