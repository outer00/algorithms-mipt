#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int target;
  std::cin >> target;

  std::vector<std::vector<long long>> dp(target + 1,
                                         std::vector<long long>(target + 1, 0));
  for (int i = 0; i <= target; ++i) {
    dp[i][0] = 0;
    dp[0][i] = 1;
  }

  for (int sum = 1; sum <= target; ++sum) {
    for (int largest = 1; largest <= target; ++largest) {
      dp[sum][largest] = sum >= largest
                             ? dp[sum][largest - 1] + dp[sum - largest][largest / 2]
                             : dp[sum][sum];
    }
  }

  std::cout << dp[target][target];
  return 0;
}
