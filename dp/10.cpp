#include <iostream>
#include <vector>

void GetAns(const std::vector<std::pair<int, int>>& dp,
            const std::vector<std::pair<int, int>>& par,
            const std::vector<int>& a, int maxlen, int maxind) {
  std::cout << maxlen << '\n';
  std::vector<int> ans(maxlen);
  bool state = dp[maxind].first <= dp[maxind].second;
  int cur = maxind;
  for (int i = maxlen - 1; i >= 0; --i) {
    ans[i] = a[cur];
    cur = (state ? par[cur].second : par[cur].first);
    state = state ^ true;
  }
  for (int i = 0; i < maxlen; ++i) {
    std::cout << ans[i] << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int maxlen = 1;
  int maxind = 0;
  std::vector<std::pair<int, int>> par(n, {-1, -1});
  std::vector<std::pair<int, int>> dp(n);
  dp[0] = std::make_pair(1, 1);
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (a[j] < a[i] && dp[i].second < dp[j].first + 1) {
        dp[i].second = dp[j].first + 1;
        par[i].second = j;
      } else if (a[j] > a[i] && dp[i].first < dp[j].second + 1) {
        dp[i].first = dp[j].second + 1;
        par[i].first = j;
      }
    }
    if (dp[i].second > maxlen || dp[i].first > maxlen) {
      maxind = i;
      maxlen = std::max(dp[i].first, dp[i].second);
    }
  }
  GetAns(dp, par, a, maxlen, maxind);
}