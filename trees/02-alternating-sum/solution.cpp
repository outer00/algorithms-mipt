#include <iostream>
#include <vector>

struct Node {
  long long sum = 0;
  long long left = 0;
  long long right = 0;
};

struct SegmentTree {
  static const long long kFirstLeaf = 131071;
  std::vector<Node> tree{kFirstLeaf * 2 + 1};

  void Build(const std::vector<long long>& values) {
    for (long long i = kFirstLeaf; i < kFirstLeaf * 2 + 1; ++i) {
      tree[i].sum = values[i - kFirstLeaf];
      tree[i].left = i - kFirstLeaf;
      tree[i].right = tree[i].left;
    }
    for (long long i = kFirstLeaf - 1; i >= 0; --i) {
      tree[i].sum = tree[2 * i + 1].sum + tree[2 * i + 2].sum;
      tree[i].left = tree[2 * i + 1].left;
      tree[i].right = tree[2 * i + 2].right;
    }
  }

  void Up(long long index, long long delta) {
    tree[index].sum += delta;
    if (index == 0) {
      return;
    }
    Up((index - 1) / 2, delta);
  }

  void Assign(long long position, long long value) {
    long long index = position + kFirstLeaf;
    long long delta = value - tree[index].sum;
    tree[index].sum += delta;
    Up((index - 1) / 2, delta);
  }

  long long GetSum(long long index, long long left, long long right) {
    if (left <= tree[index].left && tree[index].right <= right) {
      return tree[index].sum;
    }
    if (tree[index].left > right || tree[index].right < left) {
      return 0;
    }
    return GetSum(2 * index + 1, left, right) +
           GetSum(2 * index + 2, left, right);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int size;
  std::cin >> size;

  std::vector<long long> values(SegmentTree::kFirstLeaf + 2, 0);
  for (int i = 0; i < size; ++i) {
    long long value;
    std::cin >> value;
    values[i] = i % 2 == 0 ? value : -value;
  }

  SegmentTree tree;
  tree.Build(values);

  int queries;
  std::cin >> queries;
  for (int i = 0; i < queries; ++i) {
    int command;
    int first;
    int second;
    std::cin >> command >> first >> second;
    --first;
    if (command == 0) {
      tree.Assign(first, first % 2 == 0 ? second : -second);
    } else {
      --second;
      long long sum = tree.GetSum(0, first, second);
      std::cout << (first % 2 == 0 ? sum : -sum) << '\n';
    }
  }

  return 0;
}
