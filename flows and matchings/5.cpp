#include "climits"
#include "iostream"
#include "vector"
int bypass = INT_MAX;
int num;

struct Graph {
  std::vector<std::vector<int>> matrix;
  std::vector<bool> visited;
  explicit Graph(int nn)
      : matrix(nn + 1, std::vector<int>(nn + 1)), visited(nn + 1, false) {}
  bool DFS(int from, int to, int weight) {
    if (from == to) {
      bypass = weight;
      return true;
    }
    visited[from] = true;
    for (int i = 1; i <= num; ++i) {
      if (matrix[from][i] != 0 && !visited[i]) {
        if (DFS(i, to, std::min(weight, matrix[from][i]))) {
          matrix[i][from] += bypass;
          matrix[from][i] -= bypass;
          return true;
        }
      }
    }
    return false;
  }
};

int main() {
  int answer = 0;
  int mnum;
  std::cin >> num >> mnum;
  Graph graph(num);
  int from;
  int to;
  for (int i = 0; i < mnum; ++i) {
    std::cin >> from >> to >> graph.matrix[from][to];
  }
  while (graph.DFS(1, num, INT_MAX)) {
    answer += bypass;
    bypass = INT_MAX;
    graph.visited.assign(num + 1, false);
  }
  std::cout << answer;
}