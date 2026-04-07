#include <iostream>
#include <vector>

const int cKIntMax = 30000;

struct Edge {
  int from;
  int to;
  int weight;
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void FordBellman(int num, int mnum, std::vector<Edge>& graph) {
  std::vector<int> distances(num, cKIntMax);
  distances[0] = 0;
  int from;
  int to;
  int weight;
  for (int i = 0; i < num - 1; ++i) {
    for (int j = 0; j < mnum; ++j) {
      from = graph[j].from;
      to = graph[j].to;
      weight = graph[j].weight;
      if (distances[from] != cKIntMax &&
          distances[from] + weight < distances[to]) {
        distances[to] = distances[from] + weight;
          }
    }
  }
  for (int i = 0; i < num; ++i) {
    distances[i] == cKIntMax ? std::cout << cKIntMax << ' '
                             : std::cout << distances[i] << ' ';
  }
}

int main() {
  OptimizeIO();
  int num;
  int mnum;
  std::cin >> num >> mnum;
  std::vector<Edge> graph(mnum);
  for (int i = 0; i < mnum; ++i) {
    std::cin >> graph[i].from >> graph[i].to >> graph[i].weight;
    --graph[i].to;
    --graph[i].from;
  }
  FordBellman(num, mnum, graph);
}