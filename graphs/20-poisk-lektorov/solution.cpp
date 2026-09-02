#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

class DSU {
 public:
  explicit DSU(int size) : parent_(size + 1, -1), size_(size + 1, 1) {}

  void Unite(int first, int second) {
    first = Find(first);
    second = Find(second);
    if (first == second) {
      return;
    }
    if (size_[first] < size_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    size_[first] = std::max(size_[second] + 1, size_[first]);
  }

  bool Connected(int first, int second) { return Find(first) == Find(second); }

 private:
  std::vector<int> parent_;
  std::vector<int> size_;

  int Find(int vertex) {
    if (parent_[vertex] == -1 || parent_[vertex] == vertex) {
      return vertex;
    }
    return Find(parent_[vertex]);
  }
};

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  int lecturers;
  std::cin >> lecturers;

  std::vector<std::vector<int>> meeting_cost(
      lecturers + 1, std::vector<int>(lecturers + 1));
  for (int i = 0; i < lecturers; ++i) {
    for (int j = 0; j < lecturers; ++j) {
      std::cin >> meeting_cost[i][j];
    }
  }

  std::vector<std::tuple<int, int, int>> edges;
  for (int i = 1; i <= lecturers; ++i) {
    int invite_cost;
    std::cin >> invite_cost;
    edges.emplace_back(invite_cost, 0, i);
  }
  for (int i = 0; i < lecturers; ++i) {
    for (int j = i + 1; j < lecturers; ++j) {
      edges.emplace_back(meeting_cost[i][j], i + 1, j + 1);
    }
  }

  std::sort(edges.begin(), edges.end());

  DSU dsu(lecturers);
  int answer = 0;
  int taken = 0;
  for (size_t i = 0; i < edges.size() && taken < lecturers; ++i) {
    auto [cost, from, to] = edges[i];
    if (!dsu.Connected(from, to)) {
      answer += cost;
      ++taken;
      dsu.Unite(from, to);
    }
  }

  std::cout << answer;
  return 0;
}
