#include <iostream>
#include <map>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  const long long cMod = 1e9 + 7;

  int count;
  std::cin >> count;
  std::vector<long long> values(count + 1);
  for (int i = 1; i <= count; ++i) {
    std::cin >> values[i];
  }

  std::vector<long long> dp(count + 1);
  dp[0] = 1;

  std::map<long long, long long> last_position;
  for (int i = 1; i <= count; ++i) {
    dp[i] = dp[i - 1] * 2;
    if (last_position.find(values[i]) != last_position.end()) {
      dp[i] -= dp[last_position[values[i]]];
    }
    dp[i] = (dp[i] + cMod) % cMod;
    last_position[values[i]] = i - 1;
  }

  std::cout << dp[count] - 1;
  return 0;
}
