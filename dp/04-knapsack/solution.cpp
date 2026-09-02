#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int count;
  int capacity;
  std::cin >> count >> capacity;

  std::vector<int> weights(count + 1);
  std::vector<int> costs(count + 1);
  for (int i = 1; i <= count; ++i) {
    std::cin >> weights[i];
  }
  for (int i = 1; i <= count; ++i) {
    std::cin >> costs[i];
  }

  std::vector<std::vector<int>> dp(count + 1, std::vector<int>(capacity + 1, 0));
  std::vector<std::vector<std::pair<int, int>>> parent(
      count + 1, std::vector<std::pair<int, int>>(capacity + 1, {0, 0}));

  for (int i = 1; i <= count; ++i) {
    for (int weight = 1; weight <= capacity; ++weight) {
      dp[i][weight] = dp[i - 1][weight];
      parent[i][weight] = {i - 1, weight};
      if (weight >= weights[i] &&
          dp[i][weight] < dp[i - 1][weight - weights[i]] + costs[i]) {
        dp[i][weight] = dp[i - 1][weight - weights[i]] + costs[i];
        parent[i][weight] = {i - 1, weight - weights[i]};
      }
    }
  }

  auto current = parent[count][capacity];
  if (current.second != capacity) {
    std::cout << count << '\n';
  }
  while (true) {
    auto previous = parent[current.first][current.second];
    if (previous.second != current.second && current.first != 0) {
      std::cout << current.first << '\n';
    }
    current = previous;
    if (current.first == 0 || current.second == 0) {
      break;
    }
  }
  return 0;
}
