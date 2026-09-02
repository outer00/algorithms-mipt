#include <iostream>
#include <vector>

bool IsCorrect(int mask, const std::vector<int>& column, int height) {
  for (int i = 1; i <= height; ++i) {
    if ((mask & 1) != column[i] && column[i] != 2) {
      return false;
    }
    mask >>= 1;
  }
  return true;
}

bool IsBalanced(int left_mask, int right_mask, int height) {
  int left_bit = left_mask & 1;
  int right_bit = right_mask & 1;
  for (int i = 1; i < height; ++i) {
    left_mask >>= 1;
    right_mask >>= 1;
    int next_left_bit = left_mask & 1;
    int next_right_bit = right_mask & 1;
    if (left_bit + right_bit + next_left_bit + next_right_bit != 2) {
      return false;
    }
    left_bit = next_left_bit;
    right_bit = next_right_bit;
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  const long long cMod = 1e9 + 7;

  int rows;
  int cols;
  std::cin >> rows >> cols;

  std::vector<std::vector<int>> columns(cols + 1, std::vector<int>(rows + 1));
  for (int i = 1; i <= rows; ++i) {
    for (int j = 1; j <= cols; ++j) {
      char cell;
      std::cin >> cell;
      if (cell == '-') {
        columns[j][i] = 0;
      } else if (cell == '+') {
        columns[j][i] = 1;
      } else {
        columns[j][i] = 2;
      }
    }
  }

  std::vector<long long> current(1 << rows, 0);
  std::vector<long long> next(1 << rows, 0);

  for (int mask = 0; mask < (1 << rows); ++mask) {
    if (IsCorrect(mask, columns[1], rows)) {
      current[mask] = 1;
    }
  }

  for (int j = 1; j < cols; ++j) {
    for (int mask = 0; mask < (1 << rows); ++mask) {
      if (!IsCorrect(mask, columns[j], rows)) {
        continue;
      }
      int same = mask;
      int inverted = ((1 << rows) - 1) ^ mask;
      if (IsBalanced(mask, same, rows) && IsCorrect(same, columns[j + 1], rows)) {
        next[same] = (next[same] + current[mask]) % cMod;
      }
      if (IsBalanced(mask, inverted, rows) &&
          IsCorrect(inverted, columns[j + 1], rows)) {
        next[inverted] = (next[inverted] + current[mask]) % cMod;
      }
    }
    std::swap(next, current);
    next.assign(1 << rows, 0);
  }

  long long answer = 0;
  for (int mask = 0; mask < (1 << rows); ++mask) {
    answer = (answer + current[mask]) % cMod;
  }

  std::cout << answer;
  return 0;
}
