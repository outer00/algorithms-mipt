#include <iostream>
#include <list>
#include <tuple>
#include <utility>
#include <vector>

void PrintAnswer(const std::list<long long>& answer) {
  std::cout << answer.size() << "\n";
  for (long long edge_id : answer) {
    std::cout << edge_id << " ";
  }
}

int main() {
  const long long cInf = 1e17;

  long long vertices;
  long long edges;
  long long talks;
  std::cin >> vertices >> edges >> talks;

  std::vector<std::vector<std::pair<long long, long long>>> parent(
      vertices, std::vector<std::pair<long long, long long>>(vertices, {-1, -1}));
  std::vector<std::vector<long long>> dist(vertices,
                                           std::vector<long long>(vertices, cInf));
  for (long long i = 0; i < vertices; ++i) {
    dist[i][i] = 0;
  }

  for (long long i = 0; i < edges; ++i) {
    long long from;
    long long to;
    long long mood;
    std::cin >> from >> to >> mood;
    --from;
    --to;
    if (-mood < dist[from][to]) {
      dist[from][to] = -mood;
      parent[from][to] = {from, i + 1};
    }
  }

  std::vector<long long> route(talks);
  for (long long& city : route) {
    std::cin >> city;
    --city;
  }

  for (long long middle = 0; middle < vertices; ++middle) {
    for (long long from = 0; from < vertices; ++from) {
      if (dist[from][middle] == cInf) {
        continue;
      }
      for (long long to = 0; to < vertices; ++to) {
        if (dist[middle][to] == cInf) {
          continue;
        }
        if (dist[from][middle] + dist[middle][to] < dist[from][to]) {
          dist[from][to] = dist[from][middle] + dist[middle][to];
          parent[from][to] = parent[middle][to];
        }
      }
    }
  }

  for (long long cycle = 0; cycle < vertices; ++cycle) {
    if (dist[cycle][cycle] >= 0) {
      continue;
    }
    for (long long from = 0; from < vertices; ++from) {
      if (dist[from][cycle] == cInf) {
        continue;
      }
      for (long long to = 0; to < vertices; ++to) {
        if (dist[cycle][to] != cInf) {
          dist[from][to] = -cInf;
        }
      }
    }
  }

  for (long long i = 0; i + 1 < talks; ++i) {
    if (dist[route[i]][route[i + 1]] == -cInf) {
      std::cout << "infinitely kind\n";
      return 0;
    }
  }

  std::list<long long> answer;
  for (long long i = 0; i + 1 < talks; ++i) {
    long long from = route[i];
    long long to = route[i + 1];

    std::list<long long> path;
    long long current = to;
    while (current != from) {
      auto [previous, edge_id] = parent[from][current];
      current = previous;
      path.push_back(edge_id);
    }
    path.reverse();
    answer.insert(answer.end(), path.begin(), path.end());
  }

  PrintAnswer(answer);
  return 0;
}
