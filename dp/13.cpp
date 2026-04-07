#include <iostream>
#include <map>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  const long long cMod = 1e9 + 7;
  int n;
  std::cin >> n;
  std::vector<long long> a(n + 1);

  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }

  std::vector<long long> dp(n + 1);
  dp[0] = 1;
  std::map<long long, long long> m;
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i - 1] * 2;
    if (m.find(a[i]) != m.end()) {
      dp[i] -= dp[m[a[i]]];
    }
    dp[i] = (dp[i] + cMod) % cMod;
    m[a[i]] = i - 1;
  }
  std::cout << dp[n] - 1;
}