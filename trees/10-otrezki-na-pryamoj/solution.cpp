#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

class Treap {
 public:
  long long GetAns() { return GetSum(root_); }

  struct Node {
    long long value, priority, subtree_size;
    long long len, len_sum;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(long long value, long long priority, long long len)
        : value(value), priority(priority), subtree_size(1), len(len), len_sum(len * len) {}
  };

  Treap() : root_(nullptr) {}

  ~Treap() { Clear(root_); }

  void Clear(Node*& node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  void Insert(long long x, long long priority, long long len) {
    if (Exists(x)) {
      return;
    }
    Node* node = new Node(x, priority, len);
    Node* left;
    Node* right;
    Split(root_, left, right, x);
    Merge(left, left, node);
    Merge(root_, left, right);
  }

  void Erase(long long x) {
    if (!Exists(x)) {
      return;
    }

    Node* left_with_x;
    Node* right;
    Node* left;
    Node* node_x;
    Split(root_, left_with_x, right, x);
    Split(left_with_x, left, node_x, x - 1);
    Merge(root_, left, right);
    delete node_x;
  }

  bool Exists(long long x) {
    Node* current = root_;
    while (current != nullptr) {
      if (current->value == x) {
        return true;
      }
      if (current->value < x) {
        current = current->right;
      } else {
        current = current->left;
      }
    }
    return false;
  }

  Node* Next(long long x) {
    Node* current = root_;
    Node* result = nullptr;
    while (current != nullptr) {
      if (current->value > x) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return result;
  }

  Node* Prev(long long x) {
    Node* current = root_;
    Node* result = nullptr;
    while (current != nullptr) {
      if (current->value >= x) {
        current = current->left;
      } else {
        result = current;
        current = current->right;
      }
    }
    return result;
  }

  Node* Kth(long long k) {
    Node* current = root_;
    while (current != nullptr) {
      int left_size = GetSize(current->left);
      if (left_size >= k) {
        current = current->left;
      } else if (left_size == k - 1) {
        return current;
      } else {
        current = current->right;
        k -= left_size + 1;
      }
    }
    return nullptr;
  }

 private:
  Node* root_;

  static long long GetSize(Node*& node) {
    if (node != nullptr) {
      return node->subtree_size;
    }
    return 0;
  }

  static long long GetSum(Node*& node) {
    if (node != nullptr) {
      return node->len_sum;
    }
    return 0;
  }

  static void Update(Node*& node) {
    if (node != nullptr) {
      node->subtree_size = GetSize(node->left) + GetSize(node->right) + 1;
    }
    if (node != nullptr) {
      node->len_sum =
          GetSum(node->left) + GetSum(node->right) + node->len * node->len;
    }
  }

  void Merge(Node*& tree, Node* left, Node* right) {
    if (left == nullptr) {
      tree = right;
    } else if (right == nullptr) {
      tree = left;
    } else if (left->priority < right->priority) {
      Merge(left->right, left->right, right);
      tree = left;
    } else {
      Merge(right->left, left, right->left);
      tree = right;
    }
    Update(tree);
  }

  void Split(Node* tree, Node*& left, Node*& right, long long k) {
    if (tree == nullptr) {
      left = right = nullptr;
    } else if (tree->value <= k) {
      Split(tree->right, tree->right, right, k);
      left = tree;
    } else {
      Split(tree->left, left, tree->left, k);
      right = tree;
    }
    Update(tree);
  }
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
}

int main() {
  const int kMaxSegments = 1e6;
  OptimizeIO();

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::vector<long long> priorities(kMaxSegments);
  std::iota(priorities.begin(), priorities.end(), 0);
  std::shuffle(priorities.begin(), priorities.end(), generator);

  int used_priorities = 0;
  Treap treap;

  int count;
  std::cin >> count;
  int position = 0;
  for (int i = 0; i < count; ++i) {
    int length;
    std::cin >> length;
    treap.Insert(position, priorities[++used_priorities], length);
    position += length;
  }

  int queries;
  std::cin >> queries;
  std::cout << treap.GetAns() << '\n';
  for (int i = 0; i < queries; ++i) {
    int command;
    long long index;
    std::cin >> command >> index;
    if (command == 1) {
      Treap::Node* current = treap.Kth(index);
      long long length = current->len;
      long long start = current->value;
      Treap::Node* next = treap.Next(start);
      Treap::Node* prev = treap.Prev(start);
      if (next == nullptr) {
        long long prev_start = prev->value;
        long long prev_length = prev->len;
        treap.Erase(prev_start);
        treap.Erase(start);
        treap.Insert(prev_start, priorities[++used_priorities],
                     prev_length + length);
      } else if (prev == nullptr) {
        long long next_start = next->value;
        long long next_length = next->len;
        treap.Erase(start);
        treap.Erase(next_start);
        treap.Insert(start, priorities[++used_priorities],
                     length + next_length);
      } else {
        long long prev_start = prev->value;
        long long prev_length = prev->len;
        long long next_start = next->value;
        long long next_length = next->len;
        treap.Erase(start);
        treap.Erase(prev_start);
        treap.Erase(next_start);
        treap.Insert(prev_start, priorities[++used_priorities],
                     prev_length + length / 2);
        treap.Insert(start + length / 2, priorities[++used_priorities],
                     next_length + length - length / 2);
      }
    } else {
      Treap::Node* current = treap.Kth(index);
      long long start = current->value;
      long long length = current->len;
      treap.Erase(start);
      treap.Insert(start, priorities[count + i], length / 2);
      treap.Insert(start + length / 2, priorities[count + i + 1],
                   length - length / 2);
    }
    std::cout << treap.GetAns() << '\n';
  }
  return 0;
}
