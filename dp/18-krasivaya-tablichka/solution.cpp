#include <cassert>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

class BigInteger {
 public:
  static const long long cBaseLen = 9;
  static const long long cBase = 1e9;

  static std::pair<BigInteger, BigInteger> Divide(const BigInteger& n,
                                                  const BigInteger& d);
  static BigInteger Gcd(const BigInteger& a, const BigInteger& b);

  BigInteger();
  BigInteger(int x);
  BigInteger(std::string str);
  BigInteger(const BigInteger& num);

  std::string ToString(bool no_leading_zeros = true) const;
  int Compare(const BigInteger& num) const;
  void ChangeSign();
  void Shift();

  BigInteger& operator=(BigInteger num);
  BigInteger& operator+=(const BigInteger& num);
  BigInteger& operator-=(const BigInteger& num);
  BigInteger& operator*=(const BigInteger& num);
  BigInteger& operator/=(const BigInteger& num);
  BigInteger& operator%=(const BigInteger& num);
  BigInteger operator-() const;
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

  explicit operator bool() const;

  bool is_negative = false;
  std::vector<long long> digits;

  static size_t GetNumberLength(long long x);
  static size_t GetNumberLength(std::string str);
  static long long FindBaseDivider(const BigInteger& n, const BigInteger& d);

  void Swap(BigInteger& num);
  void RemoveLeadingZeros();
};

BigInteger operator+(BigInteger lhs, const BigInteger& rhs);
BigInteger operator-(BigInteger lhs, const BigInteger& rhs);
BigInteger operator*(BigInteger lhs, const BigInteger& rhs);
BigInteger operator/(BigInteger lhs, const BigInteger& rhs);
BigInteger operator%(BigInteger lhs, const BigInteger& rhs);
bool operator==(const BigInteger& lhs, const BigInteger& rhs);
bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
bool operator<(const BigInteger& lhs, const BigInteger& rhs);
bool operator>(const BigInteger& lhs, const BigInteger& rhs);
bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
BigInteger operator""_bi(unsigned long long x);
BigInteger operator""_bi(const char* str, size_t /*unused*/);

std::ostream& operator<<(std::ostream& os, const BigInteger& num);
std::istream& operator>>(std::istream& is, BigInteger& num);

size_t BigInteger::GetNumberLength(long long x) {
  if (x == 0) {
    return 1;
  }
  return std::ceil(std::log(std::abs(x) + 1) / std::log(cBase));
}

size_t BigInteger::GetNumberLength(std::string str) {
  size_t sz = str.size();
  if (str[0] == '-') {
    --sz;
  }
  return (sz + cBaseLen - 1) / cBaseLen;
}

BigInteger::BigInteger() : is_negative(false) {}

BigInteger::BigInteger(int x)
    : is_negative(x < 0), digits(GetNumberLength(x), 0) {
  x = std::abs(x);
  for (size_t i = 0; i < digits.size(); ++i) {
    digits[i] = x % cBase;
    x /= cBase;
  }
}

BigInteger::BigInteger(std::string str)
    : is_negative(str[0] == '-'), digits(GetNumberLength(str), 0) {
  size_t k = 0;
  int start = str.size();
  int end = 0;
  if (is_negative) {
    ++end;
  }
  for (int i = start; i > end; i -= cBaseLen) {
    if (i >= cBaseLen) {
      digits[k++] = stoi(str.substr(i - cBaseLen, cBaseLen));
    } else {
      digits[k++] = stoi(str.substr(end, i - end));
    }
  }
  RemoveLeadingZeros();
}

BigInteger::BigInteger(const BigInteger& num)
    : is_negative(num.is_negative), digits(num.digits) {}

std::string BigInteger::ToString(bool no_leading_zeros) const {
  std::stringstream ss;
  if (is_negative) {
    ss << '-';
  }
  auto iter = digits.rbegin();
  ss << std::setfill('0');
  if (!no_leading_zeros) {
    ss << std::setw(cBaseLen);
  }
  ss << *iter++;
  for (; iter != digits.rend(); ++iter) {
    ss << std::setw(cBaseLen) << *iter;
  }
  return ss.str();
}

void BigInteger::ChangeSign() {
  if (*this != 0) {
    is_negative ^= 1;
  }
}

BigInteger BigInteger::Gcd(const BigInteger& a, const BigInteger& b) {
  if (b == 0) {
    return a;
  }
  return Gcd(b, a % b);
}

void BigInteger::Shift() {
  if (*this != 0) {
    digits.insert(digits.begin(), 0);
  }
}

BigInteger& BigInteger::operator=(BigInteger num) {
  Swap(num);
  return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& num) {
  if (is_negative != num.is_negative) {
    if (is_negative) {
      return *this = num - (-*this);
    }
    return *this -= -num;
  }

  long long carry = 0;
  size_t n = digits.size();
  size_t m = num.digits.size();
  size_t max_size = std::max(n, m);
  for (size_t i = 0; i < max_size || carry != 0; ++i) {
    long long x = carry;
    if (i < n) {
      x += digits[i];
    }
    if (i < m) {
      x += num.digits[i];
    }
    carry = static_cast<long long>(x >= cBase);
    if (carry != 0) {
      x -= cBase;
    }

    if (i >= n) {
      digits.push_back(0);
    }
    digits[i] = x;
  }

  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& num) {
  if (num.is_negative) {
    return *this += -num;
  }
  if (*this == num) {
    return *this = 0;
  }
  if (*this < num) {
    *this = num - *this;
    is_negative = true;
    return *this;
  }

  size_t n = digits.size();
  size_t m = num.digits.size();
  long long carry = 0;
  for (size_t i = 0; i < n; ++i) {
    long long x = -carry;
    if (i < n) {
      x += digits[i];
    }
    if (i < m) {
      x -= num.digits[i];
    }
    carry = static_cast<long long>(x < 0);
    if (carry != 0) {
      x += cBase;
    }
    digits[i] = x;
  }

  RemoveLeadingZeros();
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& num) {
  size_t n = digits.size();
  size_t m = num.digits.size();
  if (n < m) {
    return *this = num * (*this);
  }

  std::vector<long long> new_digits(n + m);
  for (size_t i = 0; i < n; ++i) {
    long long carry = 0;
    for (size_t j = 0; j < m || carry != 0; ++j) {
      long long x = new_digits[i + j] + carry;
      if (j < m) {
        x += digits[i] * num.digits[j];
      }
      new_digits[i + j] = x % cBase;
      carry = x / cBase;
    }
  }

  digits = std::move(new_digits);
  RemoveLeadingZeros();
  is_negative = digits.back() != 0 && (is_negative != num.is_negative);
  return *this;
}

std::pair<BigInteger, BigInteger> BigInteger::Divide(const BigInteger& n,
                                                     const BigInteger& d) {
  if (d.is_negative) {
    auto p = Divide(n, -d);
    return {-p.first, p.second};
  }
  if (n.is_negative) {
    auto p = Divide(-n, d);
    return {-p.first, -p.second};
  }

  if (n < d) {
    return {0, n};
  }
  BigInteger q = 0;
  BigInteger r = 0;
  for (size_t i = n.digits.size(); i-- > 0;) {
    r.Shift();
    r += n.digits[i];
    if (r < d) {
      q.Shift();
      continue;
    }
    long long j = FindBaseDivider(r, d);
    r -= d * j;
    q.Shift();
    q += j;
  }

  return {q, r};
}

BigInteger& BigInteger::operator/=(const BigInteger& num) {
  return *this = Divide(*this, num).first;
}

BigInteger& BigInteger::operator%=(const BigInteger& num) {
  return *this = Divide(*this, num).second;
}

BigInteger BigInteger::operator-() const {
  BigInteger num(*this);
  if (num != 0) {
    num.is_negative ^= 1;
  }
  return num;
}

BigInteger& BigInteger::operator++() { return *this += 1; }

BigInteger BigInteger::operator++(int) {
  BigInteger copy = *this;
  ++*this;
  return copy;
}

BigInteger& BigInteger::operator--() { return *this -= 1; }

BigInteger BigInteger::operator--(int) {
  BigInteger copy = *this;
  --*this;
  return copy;
}

BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
  return lhs += rhs;
}

BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
  return lhs -= rhs;
}

BigInteger operator*(BigInteger lhs, const BigInteger& rhs) {
  return lhs *= rhs;
}

BigInteger operator/(BigInteger lhs, const BigInteger& rhs) {
  return lhs /= rhs;
}

BigInteger operator%(BigInteger lhs, const BigInteger& rhs) {
  return lhs %= rhs;
}

int BigInteger::Compare(const BigInteger& num) const {
  if (is_negative != num.is_negative) {
    return is_negative ? -1 : 1;
  }
  size_t n = digits.size();
  size_t m = num.digits.size();
  if (n != m) {
    return (is_negative ^ (n < m)) != 0 ? -1 : 1;
  }
  for (size_t i = n; i-- > 0;) {
    if (digits[i] != num.digits[i]) {
      return (is_negative ^ (digits[i] < num.digits[i])) != 0 ? -1 : 1;
    }
  }
  return 0;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
  return lhs.Compare(rhs) == 0;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs == rhs);
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
  return lhs.Compare(rhs) == -1;
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
  return rhs < lhs;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(rhs < lhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs);
}

BigInteger::operator bool() const { return digits.back() != 0; }

BigInteger operator""_bi(unsigned long long x) {
  return BigInteger(std::to_string(x));
}

BigInteger operator""_bi(const char* str, size_t /*unused*/) {
  return BigInteger(std::string(str));
}

std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
  return os << num.ToString();
}

std::istream& operator>>(std::istream& is, BigInteger& num) {
  std::string s;
  is >> s;
  num = s;
  return is;
}

void BigInteger::Swap(BigInteger& num) {
  std::swap(is_negative, num.is_negative);
  std::swap(digits, num.digits);
}

void BigInteger::RemoveLeadingZeros() {
  while (digits.size() > 1 && digits.back() == 0) {
    digits.pop_back();
  }
}

long long BigInteger::FindBaseDivider(const BigInteger& n,
                                      const BigInteger& d) {
  long long lo = 1;
  long long hi = cBase;
  while (hi - lo > 1) {
    long long mid = lo + (hi - lo) / 2;
    if (mid * d <= n) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  return lo;
}

struct Matrix {
  int rows;
  int cols;
  int mod;
  std::vector<std::vector<int>> data;

  Matrix(int rows, int cols, int mod)
      : rows(rows), cols(cols), mod(mod), data(rows, std::vector<int>(cols, 0)) {}

  int GetSum() const {
    int sum = 0;
    for (const auto& row : data) {
      for (int value : row) {
        sum = (sum + value) % mod;
      }
    }
    return sum;
  }
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.cols == rhs.rows && "matrix sizes do not match");
  Matrix result(lhs.rows, rhs.cols, lhs.mod);
  for (int i = 0; i < lhs.rows; ++i) {
    for (int j = 0; j < rhs.cols; ++j) {
      for (int k = 0; k < lhs.cols; ++k) {
        result.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
        result.data[i][j] %= result.mod;
      }
    }
  }
  return result;
}

bool IsMatch(int top_mask, int bottom_mask, int width) {
  for (int i = 1; i < width; ++i) {
    int sum = (top_mask & 1) + (bottom_mask & 1) + ((top_mask >> 1) & 1) +
              ((bottom_mask >> 1) & 1);
    if (sum == 0 || sum == 4) {
      return false;
    }
    top_mask >>= 1;
    bottom_mask >>= 1;
  }
  return true;
}

Matrix Binpow(Matrix& base, BigInteger power) {
  Matrix result(base.rows, base.rows, base.mod);
  for (int i = 0; i < result.rows; ++i) {
    result.data[i][i] = 1;
  }
  while (power > 0) {
    if (*power.digits.begin() % 2 != 0) {
      result = result * base;
    }
    power /= 2;
    base = base * base;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  BigInteger rows;
  int width;
  int mod;
  std::cin >> rows >> width >> mod;
  --rows;

  Matrix transitions(1 << width, 1 << width, mod);
  for (int top_mask = 0; top_mask < (1 << width); ++top_mask) {
    for (int bottom_mask = 0; bottom_mask < (1 << width); ++bottom_mask) {
      if (IsMatch(top_mask, bottom_mask, width)) {
        transitions.data[top_mask][bottom_mask] = 1;
      }
    }
  }

  transitions = Binpow(transitions, rows);
  std::cout << transitions.GetSum() % mod;
  return 0;
}
