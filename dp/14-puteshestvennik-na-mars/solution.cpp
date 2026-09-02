#include <iostream>
#include <utility>
#include <vector>

struct Airport {
  long long x;
  long long y;
  long long flights;
};

const long long cMod = 1e9 + 9;

std::pair<long long, long long> FibPair(long long n) {
  if (n == 0) {
    return {0, 1};
  }
  auto [fib, next_fib] = FibPair(n / 2);
  long long even = (fib * ((2 * next_fib - fib + cMod) % cMod)) % cMod;
  long long odd = (fib * fib + next_fib * next_fib) % cMod;
  if (n % 2 == 0) {
    return {even, odd};
  }
  return {odd, (even + odd) % cMod};
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  long long airport_count;
  long long line_count;
  std::cin >> airport_count >> line_count;

  std::vector<Airport> airports(airport_count);
  for (Airport& airport : airports) {
    std::cin >> airport.x >> airport.y >> airport.flights;
  }

  std::vector<long long> shifts(line_count);
  for (long long& shift : shifts) {
    std::cin >> shift;
  }

  for (long long shift : shifts) {
    long long sum = 0;
    for (const Airport& airport : airports) {
      long long height = airport.y - airport.x - shift;
      if (height < 0) {
        continue;
      }
      sum += (airport.flights % cMod) * (FibPair(height).second % cMod);
      sum %= cMod;
    }
    std::cout << (sum + cMod) % cMod << '\n';
  }
  return 0;
}
