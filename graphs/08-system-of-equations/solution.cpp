#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

const int cMax = 1e6 + 1;

int vertices;
std::vector<std::vector<std::pair<int, int>>> graph(cMax);
std::vector<std::pair<int, int>> coefficients(cMax);
std::vector<bool> visited(cMax, false);
std::vector<bool> value_used(cMax, false);
std::vector<int> values(cMax, 0);

void ComputeCoefficients(int vertex) {
  visited[vertex] = true;
  for (const auto& [next, sum] : graph[vertex]) {
    if (visited[next]) {
      continue;
    }
    coefficients[next].first = -coefficients[vertex].first;
    coefficients[next].second = sum - coefficients[vertex].second;
    ComputeCoefficients(next);
  }
}

bool TryAssign(int vertex, int value) {
  visited[vertex] = true;
  if (value_used[value] || value < 1 || value > vertices) {
    return false;
  }
  value_used[value] = true;
  values[vertex] = value;

  for (const auto& [next, sum] : graph[vertex]) {
    if (visited[next]) {
      if (value + values[next] != sum) {
        return false;
      }
      continue;
    }
    if (!TryAssign(next, sum - value)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int edges;
  std::cin >> vertices >> edges;
  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    int sum;
    std::cin >> from >> to >> sum;
    graph[from].emplace_back(to, sum);
    graph[to].emplace_back(from, sum);
  }

  coefficients[1] = {1, 0};
  ComputeCoefficients(1);

  int positive = 0;
  int negative = INT_MAX;
  for (int vertex = 1; vertex <= vertices; ++vertex) {
    if (coefficients[vertex].first == 1) {
      positive = std::min(positive, coefficients[vertex].second);
    } else {
      negative = std::min(negative, coefficients[vertex].second);
    }
  }

  visited.assign(cMax, false);
  if (TryAssign(1, 1 - positive)) {
    for (int vertex = 1; vertex <= vertices; ++vertex) {
      std::cout << values[vertex] << ' ';
    }
    return 0;
  }

  visited.assign(cMax, false);
  values.assign(cMax, 0);
  value_used.assign(cMax, false);
  TryAssign(1, negative - 1);
  for (int vertex = 1; vertex <= vertices; ++vertex) {
    std::cout << values[vertex] << ' ';
  }
  return 0;
}
