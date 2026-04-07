#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

class Treap {
 public:
  long long GetAns() { return GetSum(root_); }

  struct Node {
    long long val, priority, subtree_size;
    long long len, len_sum;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(long long v, long long p, long long l)
        : val(v), priority(p), subtree_size(1), len(l), len_sum(l * l) {}
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
    Node* cur = root_;
    while (cur != nullptr) {
      if (cur->val == x) {
        return true;
      }
      if (cur->val < x) {
        cur = cur->right;
      } else {
        cur = cur->left;
      }
    }
    return false;
  }

  Node* Next(long long x) {
    Node* cur = root_;
    Node* res = nullptr;
    while (cur != nullptr) {
      if (cur->val > x) {
        res = cur;
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    return res;
  }

  Node* Prev(long long x) {
    Node* cur = root_;
    Node* res = nullptr;
    while (cur != nullptr) {
      if (cur->val >= x) {
        cur = cur->left;
      } else {
        res = cur;
        cur = cur->right;
      }
    }
    return res;
  }

  Node* Kth(long long k) {
    Node* cur = root_;
    while (cur != nullptr) {
      int left_size = GetSize(cur->left);
      if (left_size >= k) {
        cur = cur->left;
      } else if (left_size == k - 1) {
        return cur;
      } else {
        cur = cur->right;
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
    } else if (tree->val <= k) {
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
  const int cMax = 1e6;
  OptimizeIO();
  srand(time(NULL));

  std::random_device rd;
  std::mt19937 generator(rd());
  std::vector<long long> priorities(cMax);
  std::iota(priorities.begin(), priorities.end(), 0);
  std::shuffle(priorities.begin(), priorities.end(), generator);
  int k = 0;
  Treap treap;
  int n;
  std::cin >> n;
  int fst = 0;
  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    treap.Insert(fst, priorities[++k], temp);
    fst += temp;
  }
  int q;
  std::cin >> q;
  std::cout << treap.GetAns() << '\n';
  for (int i = 0; i < q; ++i) {
    int a;
    long long b;
    std::cin >> a >> b;
    // --b;
    if (a == 1) {
      Treap::Node* cur = treap.Kth(b);
      long long len = cur->len;
      long long st = cur->val;
      Treap::Node* next = treap.Next(st);
      Treap::Node* prev = treap.Prev(st);
      if (next == nullptr) {
        long long prevst = prev->val;
        long long prevlen = prev->len;
        treap.Erase(prevst);
        treap.Erase(st);
        treap.Insert(prevst, priorities[++k], prevlen + len);
      } else if (prev == nullptr) {
        long long nextlen = next->len;
        long long nextst = next->val;
        treap.Erase(st);
        treap.Erase(nextst);
        treap.Insert(st, priorities[++k], len + nextlen);
      } else {
        long long prevst = prev->val;
        long long prevlen = prev->len;
        long long nextst = next->val;
        long long nextlen = next->len;
        treap.Erase(st);
        treap.Erase(prevst);
        treap.Erase(nextst);
        treap.Insert(prevst, priorities[++k], prevlen + len / 2);
        treap.Insert(st + len / 2, priorities[++k], nextlen + len - len / 2);
      }
    } else {
      Treap::Node* cur = treap.Kth(b);
      long long st = cur->val;
      long long len = cur->len;
      treap.Erase(st);
      treap.Insert(st, priorities[n + i], len / 2);
      treap.Insert(st + len / 2, priorities[n + i + 1], len - len / 2);
    }
    std::cout << treap.GetAns() << '\n';
  }
  return 0;
}
