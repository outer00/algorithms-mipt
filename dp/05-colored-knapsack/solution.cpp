#include <algorithm>
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

  int count;
  int colors;
  int capacity;
  std::cin >> count >> colors >> capacity;

  std::vector<std::vector<Item>> by_color(colors + 1);
  for (int i = 0; i < count; ++i) {
    Item item;
    int color;
    std::cin >> item.weight >> item.cost >> color;
    by_color[color].push_back(item);
  }

  std::vector<int> dp(capacity + 1, 0);
  for (int color = 1; color <= colors; ++color) {
    for (int weight = capacity; weight > 0; --weight) {
      for (const Item& item : by_color[color]) {
        if (weight >= item.weight) {
          dp[weight] = std::max(dp[weight], dp[weight - item.weight] + item.cost);
        }
      }
    }
  }

  std::cout << dp[capacity];
  return 0;
}
