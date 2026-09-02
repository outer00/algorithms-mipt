#include <iostream>
#include <string>
#include <vector>

struct Treap {
  struct Node {
    int key, subtree_size;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int key) : key(key), subtree_size(1) {}

    Node* Find(int key) {
      Node* current = this;
      while (true) {
        if (current->key == key) {
          return current;
        }
        if (key < current->key) {
          if (current->left == nullptr) {
            return current;
          }
          current = current->left;
        } else if (key > current->key) {
          if (current->right == nullptr) {
            return current;
          }
          current = current->right;
        }
      }
    }

    Node* AddLeft(int key) {
      left = new Node(key);
      left->parent = this;
      return left;
    }

    Node* AddRight(int key) {
      right = new Node(key);
      right->parent = this;
      return right;
    }

    void RotateLeft() {
      int left_size = (left == nullptr ? 0 : left->subtree_size);
      int right_size = (right == nullptr ? 0 : right->subtree_size);
      int cnt = subtree_size - left_size - right_size;
      subtree_size = parent->subtree_size;
      parent->subtree_size -= right_size;

      parent->subtree_size -= cnt;
      Node* node_parent = parent;
      if (node_parent == nullptr) {
        return;
      }
      Node* grandparent = node_parent->parent;

      node_parent->right = left;
      if (left != nullptr) {
        left->parent = node_parent;
      }

      left = node_parent;
      node_parent->parent = this;

      parent = grandparent;
      if (grandparent != nullptr) {
        if (grandparent->left == node_parent) {
          grandparent->left = this;
        } else {
          grandparent->right = this;
        }
      }
    }

    void RotateRight() {
      int left_size = (left == nullptr ? 0 : left->subtree_size);
      int right_size = (right == nullptr ? 0 : right->subtree_size);
      int cnt = subtree_size - left_size - right_size;
      subtree_size = parent->subtree_size;
      parent->subtree_size -= left_size;
      parent->subtree_size -= cnt;
      Node* node_parent = parent;
      if (node_parent == nullptr) {
        return;
      }
      Node* grandparent = node_parent->parent;

      node_parent->left = right;
      if (right != nullptr) {
        right->parent = node_parent;
      }

      right = node_parent;
      node_parent->parent = this;

      parent = grandparent;
      if (grandparent != nullptr) {
        if (grandparent->left == node_parent) {
          grandparent->left = this;
        } else {
          grandparent->right = this;
        }
      }
    }

    void ZigZig(bool is_left_son) {
      if (is_left_son) {
        parent->RotateRight();
        RotateRight();
      } else {
        parent->RotateLeft();
        RotateLeft();
      }
    }

    void Zig(bool is_left_son) { is_left_son ? RotateRight() : RotateLeft(); }

    void ZigZag(bool is_left_son) {
      if (is_left_son) {
        RotateRight();
        RotateLeft();
      } else {
        RotateLeft();
        RotateRight();
      }
    }

    Node* Splay() {
      while (parent != nullptr) {
        bool is_left_son = IsLeftSon();
        if (parent->parent == nullptr) {
          Zig(is_left_son);
          continue;
        }
        if (is_left_son == parent->IsLeftSon()) {
          ZigZig(is_left_son);
        } else {
          ZigZag(is_left_son);
        }
      }
      return this;
    }

    bool IsLeftSon() const { return this == parent->left; }
  };

  Node* root = nullptr;

  ~Treap() { Clear(root); }

  void Clear(Node*& node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  void Insert(int key) {
    if (root == nullptr) {
      root = new Node(key);
      return;
    }
    Node* place = root->Find(key);
    if (place == nullptr) {
      return;
    }
    if (place->key == key) {
      root = place->Splay();
      ++place->subtree_size;
      return;
    }
    Node* new_node =
        (key < place->key ? place->AddLeft(key) : place->AddRight(key));
    while (place != nullptr) {
      ++place->subtree_size;
      place = place->parent;
    }
    root = new_node->Splay();
  }

  void Delete(int key) {
    if (root == nullptr) {
      return;
    }

    Node* old_value = root->Find(key);

    if (old_value->key != key) {
      return;
    }

    root = old_value->Splay();

    int left_size = (old_value->left == nullptr ? 0 : old_value->left->subtree_size);
    int right_size =
        (old_value->right == nullptr ? 0 : old_value->right->subtree_size);
    if ((old_value->subtree_size - left_size - right_size) > 1) {
      --old_value->subtree_size;
      return;
    }

    if (old_value->left == nullptr && old_value->right == nullptr) {
      delete old_value;
      root = nullptr;
    } else if (old_value->left == nullptr) {
      root = old_value->right;
      old_value->right = nullptr;
      root->parent = nullptr;
      delete old_value;
    } else if (old_value->right == nullptr) {
      root = old_value->left;
      old_value->left = nullptr;
      root->parent = nullptr;
      delete old_value;
    } else {
      --old_value->subtree_size;
      Node* new_root = old_value->left;
      --new_root->subtree_size;
      while (new_root->right != nullptr) {
        new_root = new_root->right;
        --new_root->subtree_size;
      }
      std::swap(new_root->key, old_value->key);
      (new_root == new_root->parent->left ? new_root->parent->left
                                        : new_root->parent->right) =
          new_root->left;
      if (new_root->left != nullptr) {
        new_root->left->parent = new_root->parent;
      }
      new_root->left = new_root->right = new_root->parent = nullptr;
      delete new_root;
    }
  }

  int LessCnt(int val) {
    if (root == nullptr) {
      return 0;
    }
    root = root->Find(val)->Splay();

    if (root->key < val) {
      int right_size = (root->right == nullptr ? 0 : root->right->subtree_size);
      return root->subtree_size - right_size;
    }
    return (root->left == nullptr ? 0 : root->left->subtree_size);
  }

  int SegmentCnt(int x, int y) {
    int less_than_low = LessCnt(x);
    int less_than_high = LessCnt(y + 1);
    return less_than_high - less_than_low;
  }
};

void CopyAndInsert(Treap::Node* node, Treap& result) {
  if (node == nullptr) {
    return;
  }
  int left_size = (node->left == nullptr ? 0 : node->left->subtree_size);
  int right_size = (node->right == nullptr ? 0 : node->right->subtree_size);
  int count = node->subtree_size - left_size - right_size;
  for (int i = 0; i < count; ++i) {
    result.Insert(node->key);
  }
  CopyAndInsert(node->left, result);
  CopyAndInsert(node->right, result);
}

void Merge(Treap& target, const Treap& left, const Treap& right) {
  CopyAndInsert(left.root, target);
  CopyAndInsert(right.root, target);
}

class SegmentTree {
 private:
  int n_;
  std::vector<Treap> tree_;
  std::vector<int> values_;

  void Build(int node, int start, int end) {
    if (start == end) {
      tree_[node].Insert(values_[start]);
    } else {
      int mid = (start + end) / 2;
      Build(2 * node + 1, start, mid);
      Build(2 * node + 2, mid + 1, end);
      Merge(tree_[node], tree_[2 * node + 1], tree_[2 * node + 2]);
    }
  }

  void Update(int node, int start, int end, int index, int value) {
    if (start == end) {
      tree_[node].Delete(values_[index]);
      tree_[node].Insert(value);
      values_[index] = value;
    } else {
      int old_value = values_[index];
      int mid = (start + end) / 2;
      if (start <= index && index <= mid) {
        Update(2 * node + 1, start, mid, index, value);
      } else {
        Update(2 * node + 2, mid + 1, end, index, value);
      }
      tree_[node].Delete(old_value);
      tree_[node].Insert(value);
      values_[index] = value;
    }
  }

  int Query(int node, int start, int end, int l, int r,
            std::pair<int, int> range) {
    if (r < start || end < l) {
      return 0;
    }
    if (l <= start && end <= r) {
      return tree_[node].SegmentCnt(range.first, range.second);
    }
    int mid = (start + end) / 2;
    int left_sum = Query(2 * node + 1, start, mid, l, r, range);
    int right_sum = Query(2 * node + 2, mid + 1, end, l, r, range);
    return left_sum + right_sum;
  }

 public:
  SegmentTree(const std::vector<int>& input_values)
      : n_((int)input_values.size()), tree_(4 * n_), values_(input_values) {
    Build(0, 0, n_ - 1);
  }

  void Update(int index, int value) { Update(0, 0, n_ - 1, index, value); }

  int Query(int l, int r, int x, int y) {
    return Query(0, 0, n_ - 1, l, r, std::make_pair(x, y));
  }
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  int size;
  int queries;
  std::cin >> size >> queries;

  std::vector<int> values(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> values[i];
  }

  SegmentTree tree(values);
  for (int i = 0; i < queries; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "GET") {
      int left;
      int right;
      int low;
      int high;
      std::cin >> left >> right >> low >> high;
      std::cout << tree.Query(left - 1, right - 1, low, high) << '\n';
    } else {
      int index;
      int value;
      std::cin >> index >> value;
      tree.Update(index - 1, value);
    }
  }
  return 0;
}
