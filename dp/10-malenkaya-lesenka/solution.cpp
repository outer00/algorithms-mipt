#include <algorithm>
#include <iostream>
#include <vector>

struct Ladder {
  int down = 0;
  int up = 0;
};

void PrintAnswer(const std::vector<Ladder>& dp,
                 const std::vector<Ladder>& parent,
                 const std::vector<int>& values, int best_length,
                 int best_index) {
  std::cout << best_length << '\n';

  std::vector<int> answer(best_length);
  bool use_up = dp[best_index].down <= dp[best_index].up;
  int current = best_index;
  for (int i = best_length - 1; i >= 0; --i) {
    answer[i] = values[current];
    current = use_up ? parent[current].up : parent[current].down;
    use_up = !use_up;
  }

  for (int value : answer) {
    std::cout << value << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int count;
  std::cin >> count;
  std::vector<int> values(count);
  for (int i = 0; i < count; ++i) {
    std::cin >> values[i];
  }

  std::vector<Ladder> dp(count);
  std::vector<Ladder> parent(count, {-1, -1});
  dp[0] = {1, 1};

  int best_length = 1;
  int best_index = 0;
  for (int i = 1; i < count; ++i) {
    for (int j = 0; j < i; ++j) {
      if (values[j] < values[i] && dp[i].up < dp[j].down + 1) {
        dp[i].up = dp[j].down + 1;
        parent[i].up = j;
      } else if (values[j] > values[i] && dp[i].down < dp[j].up + 1) {
        dp[i].down = dp[j].up + 1;
        parent[i].down = j;
      }
    }
    if (dp[i].up > best_length || dp[i].down > best_length) {
      best_index = i;
      best_length = std::max(dp[i].down, dp[i].up);
    }
  }

  PrintAnswer(dp, parent, values, best_length, best_index);
  return 0;
}
