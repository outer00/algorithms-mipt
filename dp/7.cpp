#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  std::vector<long long> dp(n + 1, 0);
  long long ans = 0;

  for (int st = 2; st <= (n / 2 - (1 - n % 2)); ++st) {
    int res = n - st;
    if (3 * st * (st - 1) / 2 < res) {
      continue;
    }

    dp.assign(res + 1, 0);
    dp[0] = 1;

    for (int x = st + 1; x <= 2 * st - 1; ++x) {
      for (int s = res; s >= x; --s) {
        dp[s] += dp[s - x];
      }
    }
    ans += dp[res];
  }
  cout << ++ans << endl;

  return 0;
}