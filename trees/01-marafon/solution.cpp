#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Node {
  long long count = 0;
  long long left = 0;
  long long right = 0;
};

struct SegmentTree {
  static const long long kLeafCount = 65536;
  std::vector<Node> tree;

  SegmentTree() { tree.resize(kLeafCount * 2 + 1); }

  void Build() {
    for (long long i = kLeafCount; i < kLeafCount * 2 + 1; ++i) {
      tree[i].count = 0;
      tree[i].left = i - kLeafCount;
      tree[i].right = tree[i].left;
    }
    for (long long i = kLeafCount - 1; i >= 0; --i) {
      tree[i].count = 0;
      tree[i].left = tree[2 * i + 1].left;
      tree[i].right = tree[2 * i + 2].right;
    }
  }

  void Up(long long index, long long delta) {
    tree[index].count += delta;
    if (index == 0) {
      return;
    }
    Up((index - 1) / 2, delta);
  }

  void Insert(long long page, long long delta = 1) {
    long long index = kLeafCount + page;
    tree[index].count += delta;
    Up((index - 1) / 2, delta);
  }

  void MoveUser(long long prev_page, long long new_page) {
    Insert(prev_page, -1);
    Insert(new_page, 1);
  }

  long long GetPrefixSum(long long index, long long last_page) {
    if (tree[2 * index + 1].right == last_page) {
      return tree[2 * index + 1].count;
    }
    if (tree[2 * index + 1].right > last_page) {
      return GetPrefixSum(2 * index + 1, last_page);
    }
    return tree[2 * index + 1].count + GetPrefixSum(2 * index + 2, last_page);
  }

  long long CountBefore(long long page) { return GetPrefixSum(0, page); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  const long long kMaxUsers = 100001;
  const int kPrecision = 6;

  long long queries;
  if (!(std::cin >> queries)) {
    return 0;
  }

  std::vector<long long> user_page(kMaxUsers, 0);
  long long active_users = 0;

  SegmentTree page_tree;
  page_tree.Build();

  for (long long i = 0; i < queries; ++i) {
    std::string command;
    std::cin >> command;

    if (command == "RUN") {
      long long user;
      long long page;
      std::cin >> user >> page;
      if (user_page[user] == 0) {
        ++active_users;
        page_tree.Insert(page);
      } else {
        page_tree.MoveUser(user_page[user], page);
      }
      user_page[user] = page;
    } else if (command == "CHEER") {
      long long user;
      std::cin >> user;
      if (user_page[user] == 0) {
        std::cout << 0 << '\n';
      } else if (active_users == 1) {
        std::cout << 1 << '\n';
      } else {
        long double behind = page_tree.CountBefore(user_page[user] - 1);
        std::cout << std::fixed << std::setprecision(kPrecision)
                  << behind / (active_users - 1) << '\n';
      }
    }
  }

  return 0;
}
