#include <iostream>
#include <vector>

struct Item {
  int weight;
  int cost;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  int g;
  int m;
  std::cin >> n >> g >> m;
  std::vector<std::vector<Item>> groups(g + 1);
  for (int i = 1; i <= n; ++i) {
    Item item;
    int f;
    std::cin >> item.weight >> item.cost >> f;
    groups[f].push_back(item);
  }
  std::vector<int> dp(m + 1, 0);
  for (int color = 1; color <= g; ++color) {
    for (int j = m; j > 0; --j) {
      for (auto& item : groups[color]) {
        if (j >= item.weight) {
          dp[j] = std::max(dp[j], dp[j - item.weight] + item.cost);
        }
      }
    }
  }
  std::cout << dp[m];
}