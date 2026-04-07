#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;

  std::vector<long long> neighbors(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c;
      std::cin >> c;
      if (c == '1') {
        neighbors[i] |= (1LL << j);
      }
    }
    neighbors[i] |= (1LL << i);
  }

  long long ans = 1;
  int leftsz = n / 2;
  int rightsz = n - leftsz;

  int leftcnt = 1 << leftsz;
  std::vector<int> dp_l(leftcnt, 0);
  std::vector<int> subclicks_cnt(leftcnt, 0);
  dp_l[0] = (1 << leftsz) - 1;
  subclicks_cnt[0] = 1;

  int msb_pos = -1;
  for (int mask = 1; mask < leftcnt; ++mask) {
    if ((mask & (mask - 1)) == 0) {
      ++msb_pos;
    }
    dp_l[mask] = dp_l[mask ^ (1 << msb_pos)] &
                 static_cast<int>(neighbors[msb_pos] & ((1LL << leftsz) - 1));
    if ((mask | dp_l[mask]) != dp_l[mask]) {
      continue;
    }
    ++ans;
    subclicks_cnt[mask] = 1;
  }

  for (int bit = 0; bit < leftsz; ++bit) {
    for (int mask = 0; mask < leftcnt; ++mask) {
      if ((mask & (1 << bit)) == 0) {
        subclicks_cnt[mask | (1 << bit)] += subclicks_cnt[mask];
      }
    }
  }

  int rightcnt = 1 << rightsz;
  std::vector<int> dp_r(rightcnt, 0);
  dp_r[0] = (1 << rightsz) - 1;
  dp_l.resize(rightcnt);
  dp_l[0] = (1 << leftsz) - 1;
  msb_pos = -1;
  for (int mask = 1; mask < rightcnt; ++mask) {
    if ((mask & (mask - 1)) == 0) {
      ++msb_pos;
    }
    int prev = mask ^ (1 << msb_pos);
    dp_r[mask] = dp_r[prev] &
                 static_cast<int>(((neighbors[msb_pos + leftsz] >> leftsz)) &
                                  ((1LL << rightsz) - 1));
    dp_l[mask] = dp_l[prev] & static_cast<int>(neighbors[msb_pos + leftsz] &
                                               ((1LL << leftsz) - 1));
    if ((mask | dp_r[mask]) != dp_r[mask]) {
      continue;
    }
    ans += subclicks_cnt[dp_l[mask]];
  }

  std::cout << ans;
  return 0;
}
