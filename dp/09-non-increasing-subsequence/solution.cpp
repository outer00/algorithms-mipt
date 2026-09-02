#include <algorithm>
#include <iostream>
#include <vector>

void PrintAnswer(const std::vector<int>& tails, const std::vector<int>& parent) {
  std::cout << tails.size() << "\n";
  std::vector<int> answer(tails.size());
  int current = tails.back();
  for (int i = static_cast<int>(tails.size()) - 1; i >= 0; --i) {
    answer[i] = current + 1;
    current = parent[current];
  }
  for (int index : answer) {
    std::cout << index << " ";
  }
  std::cout << "\n";
}

int main() {
  int count;
  std::cin >> count;

  std::vector<int> values(count);
  for (int i = 0; i < count; ++i) {
    std::cin >> values[i];
  }

  std::vector<int> tails;
  std::vector<int> parent(count, -1);
  tails.push_back(0);

  for (int i = 1; i < count; ++i) {
    auto it = std::lower_bound(
        tails.begin(), tails.end(), i,
        [&](int lhs, int rhs) { return values[lhs] >= values[rhs]; });
    if (it != tails.end()) {
      parent[i] = it != tails.begin() ? *(it - 1) : -1;
      *it = i;
    } else {
      parent[i] = tails.back();
      tails.push_back(i);
    }
  }

  PrintAnswer(tails, parent);
  return 0;
}
