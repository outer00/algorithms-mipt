#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int Parent(int index) { return index & (index + 1); }

int Next(int index) { return index | (index + 1); }

void Add(std::vector<std::vector<int>>& tree, int x, int y, int size) {
  for (int i = x; i < size; i = Next(i)) {
    for (int j = y; j < size; j = Next(j)) {
      ++tree[i][j];
    }
  }
}

int GetPrefixSum(const std::vector<std::vector<int>>& tree, int x, int y) {
  if (x < 0 || y < 0) {
    return 0;
  }
  int sum = 0;
  for (int i = x; i >= 0; i = Parent(i) - 1) {
    for (int j = y; j >= 0; j = Parent(j) - 1) {
      sum += tree[i][j];
    }
  }
  return sum;
}

int GetSum(const std::vector<std::vector<int>>& tree, int x1, int y1, int x2,
           int y2) {
  int max_x = std::max(x1, x2);
  int min_x = std::min(x1, x2);
  int max_y = std::max(y1, y2);
  int min_y = std::min(y1, y2);
  return GetPrefixSum(tree, max_x, max_y) - GetPrefixSum(tree, max_x, min_y - 1) -
         GetPrefixSum(tree, min_x - 1, max_y) +
         GetPrefixSum(tree, min_x - 1, min_y - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int size;
  int queries;
  std::cin >> size >> queries;

  std::vector<std::vector<int>> tree(size, std::vector<int>(size, 0));

  for (int i = 0; i < queries; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "ADD") {
      int x;
      int y;
      std::cin >> x >> y;
      Add(tree, x - 1, y - 1, size);
    } else {
      int x1;
      int y1;
      int x2;
      int y2;
      std::cin >> x1 >> y1 >> x2 >> y2;
      std::cout << GetSum(tree, x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
    }
  }
  return 0;
}
