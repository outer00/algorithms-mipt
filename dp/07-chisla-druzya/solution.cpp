#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int target;
  std::cin >> target;

  long long answer = 1;
  std::vector<long long> dp;

  for (int smallest = 2; smallest <= target / 2 - (1 - target % 2);
       ++smallest) {
    int rest = target - smallest;
    if (3 * smallest * (smallest - 1) / 2 < rest) {
      continue;
    }

    dp.assign(rest + 1, 0);
    dp[0] = 1;

    for (int value = smallest + 1; value <= 2 * smallest - 1; ++value) {
      for (int sum = rest; sum >= value; --sum) {
        dp[sum] += dp[sum - value];
      }
    }
    answer += dp[rest];
  }

  std::cout << answer << '\n';
  return 0;
}
