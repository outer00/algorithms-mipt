#include <algorithm>
#include <iostream>
#include <vector>

int num;
int num2;
int ans_ind = 0;

auto Fill(const std::vector<int>& line, const std::vector<int>& prefix) {
  std::vector<std::vector<int>> delta(num + 1, std::vector<int>(num + 1));
  for (int i = 1; i <= num; ++i) {
    for (int j = 1; j < i; ++j) {
      int mid = (line[j] + line[i]) / 2;
      int ind = std::lower_bound(line.begin(), line.end(), mid) - line.begin();
      if (line[ind] > mid) {
        --ind;
      }
      int sum = prefix[i] - prefix[ind];
      delta[i][j] = (i - ind) * (line[i] + line[j]) - 2 * sum +
                    (num - i) * (line[j] - line[i]);
    }
  }
  return delta;
}

void Refill(std::vector<std::vector<int>>& dp,
            std::vector<std::vector<int>>& delta,
            std::vector<std::vector<int>>& par, std::vector<int>& prefix,
            std::vector<int>& line) {
  for (int i = 1; i <= num; ++i) {
    dp[0][i] = prefix[num] - 2 * prefix[i] - (num - 2 * i) * line[i];
    if (dp[0][i] < dp[0][ans_ind]) {
      ans_ind = i;
    }
  }
  for (int step = 1; step < num2; ++step) {
    ans_ind = num;
    for (int i = num; i > step; --i) {
      for (int j = step; j < i; ++j) {
        if (dp[step][i] > dp[step - 1][j] + delta[i][j]) {
          dp[step][i] = dp[step - 1][j] + delta[i][j];
          par[step][i] = j;
        }
      }
      if (dp[step][i] < dp[step][ans_ind]) {
        ans_ind = i;
      }
    }
  }
}

void GetAns(const std::vector<std::vector<int>>& dp,
            const std::vector<std::vector<int>>& par,
            const std::vector<int>& line) {
  std::cout << dp[num2 - 1][ans_ind] << "\n";
  int cur = ans_ind;
  int step = num2 - 1;
  std::vector<int> ans(num2);
  for (int i = num2 - 1; i >= 0; --i) {
    ans[i] = line[cur];
    cur = par[step--][cur];
  }
  for (auto x : ans) {
    std::cout << x << " ";
  }
}
int main() {
  const int cInf = 1e9;
  std::cin >> num >> num2;
  std::vector<int> line(num + 1);
  std::vector<int> prefix(num + 1, 0);
  for (int i = 1; i <= num; ++i) {
    std::cin >> line[i];
    prefix[i] = prefix[i - 1] + line[i];
  }
  auto delta = Fill(line, prefix);
  std::vector<std::vector<int>> dp(num2, std::vector<int>(num + 1, cInf));
  std::vector<std::vector<int>> par(num2, std::vector<int>(num + 1, -1));
  Refill(dp, delta, par, prefix, line);
  GetAns(dp, par, line);
  return 0;
}
