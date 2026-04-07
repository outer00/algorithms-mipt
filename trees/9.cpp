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

    Node* Find(int inpkey) {
      Node* cur = this;
      while (true) {
        if (cur->key == inpkey) {
          return cur;
        }
        if (inpkey < cur->key) {
          if (cur->left == nullptr) {
            return cur;
          }
          cur = cur->left;
        } else if (inpkey > cur->key) {
          if (cur->right == nullptr) {
            return cur;
          }
          cur = cur->right;
        }
      }
    }

    Node* AddLeft(int kk) {
      left = new Node(kk);
      left->parent = this;
      return left;
    }

    Node* AddRight(int kk) {
      right = new Node(kk);
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
      Node* pp = parent;
      if (pp == nullptr) {
        return;
      }
      Node* gg = pp->parent;

      pp->right = left;
      if (left != nullptr) {
        left->parent = pp;
      }

      left = pp;
      pp->parent = this;

      parent = gg;
      if (gg != nullptr) {
        if (gg->left == pp) {
          gg->left = this;
        } else {
          gg->right = this;
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
      Node* pp = parent;
      if (pp == nullptr) {
        return;
      }
      Node* gg = pp->parent;

      pp->left = right;
      if (right != nullptr) {
        right->parent = pp;
      }

      right = pp;
      pp->parent = this;

      parent = gg;
      if (gg != nullptr) {
        if (gg->left == pp) {
          gg->left = this;
        } else {
          gg->right = this;
        }
      }
    }

    void ZigZig(bool leftson) {
      if (leftson) {
        parent->RotateRight();
        RotateRight();
      } else {
        parent->RotateLeft();
        RotateLeft();
      }
    }

    void Zig(bool leftson) { leftson ? RotateRight() : RotateLeft(); }

    void ZigZag(bool leftson) {
      if (leftson) {
        RotateRight();
        RotateLeft();
      } else {
        RotateLeft();
        RotateRight();
      }
    }

    Node* Splay() {
      while (parent != nullptr) {
        bool leftson = IsLeftSon();
        if (parent->parent == nullptr) {
          Zig(leftson);
          continue;
        }
        if (leftson == parent->IsLeftSon()) {
          ZigZig(leftson);
        } else {
          ZigZag(leftson);
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
    Node* linkto = root->Find(key);
    if (linkto == nullptr || linkto->key == key) {
      return;
    }
    Node* newnode =
        (key < linkto->key ? linkto->AddLeft(key) : linkto->AddRight(key));
    while (linkto != nullptr) {
      linkto->subtree_sum += key;
      ++linkto->subtree_size;
      linkto = linkto->parent;
    }
    root = newnode->Splay();
  }

  long long LessSum(int val) {
    if (root == nullptr) {
      return 0;
    }
    root = root->Find(val)->Splay();
    long long res = 0;
    if (root->left != nullptr) {
      res += root->left->subtree_sum;
    }
    if (root->key < val) {
      res += root->key;
    }
    return res;
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
  Treap t;
  int n;
  std::cin >> n;
  char prevc = ' ';
  long long prevv = -1;
  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    if (c == '+') {
      int v;
      std::cin >> v;
      if (prevc == '?') {
        t.Insert((v + prevv) % cMod);
      } else {
        t.Insert(v);
      }
    } else {
      int l;
      int r;
      std::cin >> l >> r;
      std::cout << (prevv = t.SegmentSum(l, r)) << '\n';
      prevv %= cMod;
    }
    prevc = c;
  }
}
