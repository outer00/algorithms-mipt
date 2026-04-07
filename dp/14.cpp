#include <iostream>
#include <vector>

struct Airport {
  long long x;
  long long y;
  long long k;
};

const long long cMod = 1e9 + 9;

std::pair<long long, long long> NFib(long long n) {
  if (n == 0) {
    return {0, 1};
  }
  auto p = NFib(n / 2);
  long long a = p.first;
  long long b = p.second;
  long long c = (a * ((2 * b - a + cMod) % cMod)) % cMod;
  long long d = (a * a + b * b) % cMod;
  if (n % 2 == 0) {
    return {c, d};
  }
  return {d, (c + d) % cMod};
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  long long n;
  long long q;
  std::cin >> n >> q;
  std::vector<Airport> a(n);
  for (auto& x : a) {
    std::cin >> x.x >> x.y >> x.k;
  }
  std::vector<long long> lines(q);
  for (auto& x : lines) {
    std::cin >> x;
  }

  for (int i = 0; i < q; ++i) {
    long long s = 0;
    for (int j = 0; j < n; ++j) {
      long long x = a[j].x;
      long long y = a[j].y;
      long long k = a[j].k;
      long long c = lines[i];
      if (y < x + c) {
        continue;
      }
      s += (k % cMod) * (NFib(y - x - c).second % cMod);
      s %= cMod;
    }
    std::cout << (s + cMod) % cMod << '\n';
  }
}
