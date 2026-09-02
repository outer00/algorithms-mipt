#include <algorithm>
#include <iostream>
#include <string>
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int vertices;
  int edges;
  int queries;
  std::cin >> vertices >> edges >> queries;

  for (int i = 0; i < edges; ++i) {
    int skipped;
    std::cin >> skipped >> skipped;
  }

  std::vector<std::tuple<bool, int, int>> commands;
  int asks = 0;
  for (int i = 0; i < queries; ++i) {
    std::string command;
    int first;
    int second;
    std::cin >> command >> first >> second;
    bool is_ask = command == "ask";
    asks += static_cast<int>(is_ask);
    commands.emplace_back(is_ask, first, second);
  }

  std::reverse(commands.begin(), commands.end());

  DSU dsu(vertices);
  std::vector<bool> answers(asks);
  for (const auto& [is_ask, first, second] : commands) {
    if (is_ask) {
      answers[--asks] = dsu.Connected(first, second);
    } else {
      dsu.Unite(first, second);
    }
  }

  for (bool answer : answers) {
    std::cout << (answer ? "YES\n" : "NO\n");
  }
  return 0;
}
