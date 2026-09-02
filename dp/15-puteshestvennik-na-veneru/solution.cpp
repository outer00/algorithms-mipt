#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>

const int cMod = 1e9 + 7;
const int cMaxHeight = 16 + 1;

struct Matrix {
  int rows;
  int cols;
  std::vector<std::vector<long long>> data;

  Matrix(int rows, int cols)
      : rows(rows), cols(cols), data(rows, std::vector<long long>(cols, 0)) {}

  explicit Matrix(const std::vector<std::vector<long long>>& other)
      : rows(other.size()), cols(other[0].size()), data(other) {}
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.cols == rhs.rows && "matrix sizes do not match");
  Matrix result(lhs.rows, rhs.cols);
  for (int i = 0; i < lhs.rows; ++i) {
    for (int j = 0; j < rhs.cols; ++j) {
      for (int k = 0; k < lhs.cols; ++k) {
        result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
        result.data[i][j] %= cMod;
      }
    }
  }
  return result;
}

Matrix Binpow(Matrix& base, long long power) {
  Matrix result(base.rows, base.rows);
  for (int i = 0; i < result.rows; ++i) {
    result.data[i][i] = 1;
  }
  while (power > 0) {
    if ((power & 1) != 0) {
      result = result * base;
    }
    power /= 2;
    base = base * base;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  long long count;
  long long finish;
  std::cin >> count >> finish;

  std::vector<std::tuple<long long, long long, long long>> limits(count + 1);
  for (int i = 1; i <= count; ++i) {
    long long left;
    long long right;
    long long height;
    std::cin >> left >> right >> height;
    limits[i] = {left, right, height};
  }

  Matrix dp(count + 1, cMaxHeight);
  dp.data[0][0] = 1;

  for (int i = 1; i <= count; ++i) {
    auto [left, right, height] = limits[i];

    Matrix step(cMaxHeight, cMaxHeight);
    for (int j = 0; j <= height; ++j) {
      if (height == 0) {
        step.data[0][0] = 1;
        break;
      }
      step.data[j][j] = 1;
      if (j == 0) {
        step.data[j][j + 1] = 1;
      } else if (j == height) {
        step.data[j][j - 1] = 1;
      } else {
        step.data[j][j - 1] = step.data[j][j + 1] = 1;
      }
    }

    step = Binpow(step, std::min(right, finish) - left);
    Matrix row(std::vector<std::vector<long long>>{dp.data[i - 1]});
    step = row * step;
    dp.data[i] = step.data[0];
  }

  std::cout << dp.data[count][0];
  return 0;
}
