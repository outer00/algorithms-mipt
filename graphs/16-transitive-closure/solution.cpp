#include <iostream>
#include <vector>

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  int vertices;
  std::cin >> vertices;

  std::vector<std::vector<bool>> reachable(vertices,
                                           std::vector<bool>(vertices));
  for (int i = 0; i < vertices; ++i) {
    for (int j = 0; j < vertices; ++j) {
      int value;
      std::cin >> value;
      reachable[i][j] = value == 1;
    }
  }

  for (int middle = 0; middle < vertices; ++middle) {
    for (int from = 0; from < vertices; ++from) {
      for (int to = 0; to < vertices; ++to) {
        reachable[from][to] = reachable[from][to] ||
                              (reachable[from][middle] && reachable[middle][to]);
      }
    }
  }

  for (int from = 0; from < vertices; ++from) {
    for (int to = 0; to < vertices; ++to) {
      std::cout << (reachable[from][to] ? "1 " : "0 ");
    }
    std::cout << '\n';
  }
  return 0;
}
