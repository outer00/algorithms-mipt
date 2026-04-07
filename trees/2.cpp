#include "iostream"
#include "vector"

struct SegmentTree {
  static const long long kFirst = 131071;
  std::vector<long long[3]> tree{kFirst * 2 + 1};
  void Nothing(std::vector<long long> line) {
    for (long long i = kFirst; i < kFirst * 2 + 1; ++i) {
      tree[i][0] = line[i];
      tree[i][1] = i - kFirst;
      tree[i][2] = tree[i][1];
    }
    for (long long i = kFirst - 1; i > -1; --i) {
      tree[i][0] = tree[2 * i + 1][0] + tree[2 * i + 2][0];
      tree[i][1] = tree[2 * i + 1][1];
      tree[i][2] = tree[2 * i + 2][2];
    }
  }
  void Swap(long long ind, long long value) {
    ind += kFirst;
    long long delta = value - tree[ind][0];
    tree[ind][0] += delta;
    Up((ind - 1) / 2, delta);
  }
  void Up(long long ind, long long delta) {
    tree[ind][0] += delta;
    if (ind == 0) {
      return;
    }
    Up((ind - 1) / 2, delta);
  }
  long long GetSum(long long ind, long long left, long long right) {
    if (left <= tree[ind][1] && tree[ind][2] <= right) {
      return tree[ind][0];
    }
    if (tree[ind][1] > right || tree[ind][2] < left) {
      return 0;
    }
    return GetSum(2 * ind + 1, left, right) + GetSum(2 * ind + 2, left, right);
  }
};

int main() {
  int num;
  std::cin >> num;
  SegmentTree aaaa;
  int value;
  std::vector<long long> line(1 + 2 * SegmentTree::kFirst, 0);
  for (int i = 0; i < num; ++i) {
    std::cin >> value;
    if (i % 2 == 1) {
      value *= -1;
    }
    line[i + SegmentTree::kFirst] = value;
  }
  aaaa.Nothing(line);
  std::cin >> num;
  int command;
  int ind_or_left;
  int value_or_right;
  for (int i = 0; i < num; ++i) {
    std::cin >> command >> ind_or_left >> value_or_right;
    if (command == 0) {
      --ind_or_left;
      if (ind_or_left % 2 == 1) {
        value_or_right *= -1;
      }
      aaaa.Swap(ind_or_left, value_or_right);
    } else {
      --ind_or_left;
      --value_or_right;
      if (ind_or_left % 2 == 0) {
        std::cout << aaaa.GetSum(0, ind_or_left, value_or_right) << '\n';
      } else {
        std::cout << -aaaa.GetSum(0, ind_or_left, value_or_right) << '\n';
      }
    }
  }
  return 0;
}