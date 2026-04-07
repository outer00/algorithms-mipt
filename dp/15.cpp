#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

const int cMod = 1e9 + 7;
const int cMaxC = 16 + 1;
struct Matrix {
  int n;
  int m;
  std::vector<std::vector<long long>> data;
  Matrix(int n, int m) : n(n), m(m), data(n, std::vector<long long>(m, 0)) {}
  Matrix(const std::vector<std::vector<long long>>& oth_data)
      : n(oth_data.size()), m(oth_data[0].size()), data(oth_data) {}
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.m == rhs.n && "matrixes does not match");
  Matrix res(lhs.n, rhs.m);
  for (int i = 0; i < lhs.n; ++i) {
    for (int j = 0; j < rhs.m; ++j) {
      for (int k = 0; k < lhs.m; ++k) {
        res.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
        res.data[i][j] %= cMod;
      }
    }
  }
  return res;
}

Matrix Binpow(Matrix& a, long long p) {
  Matrix res(a.n, a.n);
  for (int i = 0; i < res.n; ++i) {
    res.data[i][i] = 1;
  }
  while (p > 0) {
    if ((p & 1) != 0) {
      res = res * a;
    }
    p /= 2;
    a = a * a;
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  long long n;
  long long k;
  std::cin >> n >> k;
  std::vector<std::tuple<long long, long long, long long>> roofs(n + 1);
  for (int i = 1; i <= n; ++i) {
    long long a;
    long long b;
    long long c;
    std::cin >> a >> b >> c;
    roofs[i] = std::make_tuple(a, b, c);
  }
  Matrix dp(n + 1, cMaxC);
  dp.data[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    long long a;
    long long b;
    long long c;
    std::tie(a, b, c) = roofs[i];
    Matrix nxt(cMaxC, cMaxC);
    for (int j = 0; j <= c; ++j) {
      if (c == 0) {
        nxt.data[0][0] = 1;
        break;
      }
      nxt.data[j][j] = 1;
      if (j == 0) {
        nxt.data[j][j + 1] = 1;
      } else if (j == c) {
        nxt.data[j][j - 1] = 1;
      } else {
        nxt.data[j][j - 1] = nxt.data[j][j + 1] = 1;
      }
    }
    nxt = Binpow(nxt, std::min(b, k) - a);
    Matrix row(std::vector<std::vector<long long>>({dp.data[i - 1]}));
    nxt = row * nxt;
    dp.data[i] = nxt.data[0];
  }
  std::cout << dp.data[n][0];
}