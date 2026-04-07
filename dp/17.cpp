#include <iostream>
#include <vector>

bool IsCorrect(int mask, const std::vector<int>& a, int n) {
  for (int i = 1; i <= n; ++i) {
    if ((mask & 1) != a[i] && a[i] != 2) {
      return false;
    }
    mask >>= 1;
  }
  return true;
}

bool IsBalanced(int mask1, int mask2, int n) {
  int prev1 = mask1 & 1;
  int prev2 = mask2 & 1;
  for (int i = 1; i < n; ++i) {
    mask1 >>= 1;
    mask2 >>= 1;
    int next1 = mask1 & 1;
    int next2 = mask2 & 1;
    if (prev1 + prev2 + next1 + next2 != 2) {
      return false;
    }
    prev1 = next1;
    prev2 = next2;
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  const long long cMod = 1e9 + 7;

  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> a(m + 1, std::vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      char c;
      std::cin >> c;
      if (c == '-') {
        a[j][i] = 0;
      } else if (c == '+') {
        a[j][i] = 1;
      } else {
        a[j][i] = 2;
      }
    }
  }

  std::vector<long long> prevlvldp(1 << n, 0LL);
  std::vector<long long> nxtlvldp(1 << n, 0LL);

  for (int mask = 0; mask < (1 << n); ++mask) {
    if (IsCorrect(mask, a[1], n)) {
      prevlvldp[mask] = 1LL;
    }
  }

  for (int j = 1; j < m; ++j) {
    for (int mask1 = 0; mask1 < (1 << n); ++mask1) {
      if (!IsCorrect(mask1, a[j], n)) {
        continue;
      }
      int nextmask1 = mask1;
      int nextmask2 = ((1 << n) - 1) ^ mask1;
      if (IsBalanced(mask1, nextmask1, n) &&
          IsCorrect(nextmask1, a[j + 1], n)) {
        nxtlvldp[nextmask1] += prevlvldp[mask1];
        nxtlvldp[nextmask1] %= cMod;
      }
      if (IsBalanced(mask1, nextmask2, n) &&
          IsCorrect(nextmask2, a[j + 1], n)) {
        nxtlvldp[nextmask2] += prevlvldp[mask1];
        nxtlvldp[nextmask2] %= cMod;
      }
    }
    std::swap(nxtlvldp, prevlvldp);
    nxtlvldp.assign(1 << n, 0LL);
  }
  long long ans = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    ans += prevlvldp[mask];
    ans %= cMod;
  }
  std::cout << ans;
}