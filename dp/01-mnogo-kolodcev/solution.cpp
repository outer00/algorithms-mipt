#include <algorithm>
#include <iostream>
#include <vector>

int houses;
int wells;
int best_index = 0;

auto BuildDelta(const std::vector<int>& positions,
                const std::vector<int>& prefix) {
  std::vector<std::vector<int>> delta(houses + 1, std::vector<int>(houses + 1));
  for (int i = 1; i <= houses; ++i) {
    for (int j = 1; j < i; ++j) {
      int middle = (positions[j] + positions[i]) / 2;
      int index = std::lower_bound(positions.begin(), positions.end(), middle) -
                  positions.begin();
      if (positions[index] > middle) {
        --index;
      }
      int sum = prefix[i] - prefix[index];
      delta[i][j] = (i - index) * (positions[i] + positions[j]) - 2 * sum +
                    (houses - i) * (positions[j] - positions[i]);
    }
  }
  return delta;
}

void FillDp(std::vector<std::vector<int>>& dp,
            std::vector<std::vector<int>>& delta,
            std::vector<std::vector<int>>& parent, std::vector<int>& prefix,
            std::vector<int>& positions) {
  for (int i = 1; i <= houses; ++i) {
    dp[0][i] = prefix[houses] - 2 * prefix[i] - (houses - 2 * i) * positions[i];
    if (dp[0][i] < dp[0][best_index]) {
      best_index = i;
    }
  }
  for (int step = 1; step < wells; ++step) {
    best_index = houses;
    for (int i = houses; i > step; --i) {
      for (int j = step; j < i; ++j) {
        if (dp[step][i] > dp[step - 1][j] + delta[i][j]) {
          dp[step][i] = dp[step - 1][j] + delta[i][j];
          parent[step][i] = j;
        }
      }
      if (dp[step][i] < dp[step][best_index]) {
        best_index = i;
      }
    }
  }
}

void PrintAnswer(const std::vector<std::vector<int>>& dp,
                 const std::vector<std::vector<int>>& parent,
                 const std::vector<int>& positions) {
  std::cout << dp[wells - 1][best_index] << "\n";
  int current = best_index;
  int step = wells - 1;
  std::vector<int> answer(wells);
  for (int i = wells - 1; i >= 0; --i) {
    answer[i] = positions[current];
    current = parent[step--][current];
  }
  for (int position : answer) {
    std::cout << position << " ";
  }
}

int main() {
  const int kInf = 1e9;
  std::cin >> houses >> wells;

  std::vector<int> positions(houses + 1);
  std::vector<int> prefix(houses + 1, 0);
  for (int i = 1; i <= houses; ++i) {
    std::cin >> positions[i];
    prefix[i] = prefix[i - 1] + positions[i];
  }

  auto delta = BuildDelta(positions, prefix);
  std::vector<std::vector<int>> dp(wells, std::vector<int>(houses + 1, kInf));
  std::vector<std::vector<int>> parent(wells, std::vector<int>(houses + 1, -1));

  FillDp(dp, delta, parent, prefix, positions);
  PrintAnswer(dp, parent, positions);
  return 0;
}
