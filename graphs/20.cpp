#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

class DSU {
  std::vector<int> parent_;
  std::vector<int> size_;
  int Get(int uv) {
    if (parent_[uv] == -1 || parent_[uv] == uv) {
      return uv;
    }
    return Get(parent_[uv]);
  }

public:
  explicit DSU(int num) : parent_(num + 1, -1), size_(num + 1, 1) {}

  void Unite(int first, int second) {
    first = Get(first);
    second = Get(second);
    if (first == second) {
      return;
    }
    if (size_[first] < size_[second]) {
      std::swap(first, second);
    }
    parent_[second] = first;
    size_[first] = std::max(size_[second] + 1, size_[first]);
  }
  bool Ask(int first, int second) { return Get(first) == Get(second); }
};

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();
  int num;
  std::cin >> num;
  DSU graph(num);
  std::vector<std::vector<int>> matr(num + 1, std::vector<int>(num + 1));
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      std::cin >> matr[i][j];
    }
  }
  int value;
  std::vector<std::tuple<int, int, int>> gr;
  for (int i = 1; i <= num; ++i) {
    std::cin >> value;
    gr.emplace_back(value, 0, i);
  }
  for (int i = 0; i < num; ++i) {
    for (int j = i + 1; j < num; ++j) {
      gr.emplace_back(matr[i][j], i + 1, j + 1);
    }
  }
  std::sort(gr.begin(), gr.end());
  int answer = 0;
  int cnter = 0;
  for (size_t i = 0; i < gr.size() && cnter < num; ++i) {
    auto [val, first, sec] = gr[i];
    if (!graph.Ask(first, sec)) {
      answer += val;
      ++cnter;
      graph.Unite(first, sec);
    }
  }
  std::cout << answer;
}
