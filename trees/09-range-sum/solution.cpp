#include <iostream>

const int cMod = 1e9;

struct Treap {
  struct Node {
    int key, subtree_size;
    long long subtree_sum;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int key) : key(key), subtree_size(1), subtree_sum(key) {}

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
      subtree_size = parent->subtree_size;
      subtree_sum = parent->subtree_sum;
      if (right != nullptr) {
        parent->subtree_size -= right->subtree_size;
        parent->subtree_sum -= right->subtree_sum;
      }
      --parent->subtree_size;
      parent->subtree_sum -= key;
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
      subtree_size = parent->subtree_size;
      subtree_sum = parent->subtree_sum;
      if (left != nullptr) {
        parent->subtree_size -= left->subtree_size;
        parent->subtree_sum -= left->subtree_sum;
      }
      --parent->subtree_size;
      parent->subtree_sum -= key;
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
    if (place == nullptr || place->key == key) {
      return;
    }
    Node* new_node =
        (key < place->key ? place->AddLeft(key) : place->AddRight(key));
    while (place != nullptr) {
      place->subtree_sum += key;
      ++place->subtree_size;
      place = place->parent;
    }
    root = new_node->Splay();
  }

  long long LessSum(int value) {
    if (root == nullptr) {
      return 0;
    }
    root = root->Find(value)->Splay();
    long long result = 0;
    if (root->left != nullptr) {
      result += root->left->subtree_sum;
    }
    if (root->key < value) {
      result += root->key;
    }
    return result;
  }

  long long SegmentSum(int l, int r) {
    long long a = LessSum(l);
    long long b = LessSum(r + 1);
    return b - a;
  }
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  Treap tree;
  int queries;
  std::cin >> queries;

  char prev_command = ' ';
  long long prev_answer = -1;
  for (int i = 0; i < queries; ++i) {
    char command;
    std::cin >> command;
    if (command == '+') {
      int value;
      std::cin >> value;
      if (prev_command == '?') {
        tree.Insert((value + prev_answer) % cMod);
      } else {
        tree.Insert(value);
      }
    } else {
      int left;
      int right;
      std::cin >> left >> right;
      prev_answer = tree.SegmentSum(left, right);
      std::cout << prev_answer << '\n';
      prev_answer %= cMod;
    }
    prev_command = command;
  }
  return 0;
}
