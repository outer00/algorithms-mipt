
#include <iostream>

// TODO: write splay-tree
struct SplayTree {
  struct Node {
    int key, size;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int key) : key(key), size(1) {}

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
      size = parent->size;
      if (right != nullptr) {
        parent->size -= right->size;
      }
      --parent->size;
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
      size = parent->size;
      if (left != nullptr) {
        parent->size -= left->size;
      }
      --parent->size;
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

  ~SplayTree() { Clear(root); }

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
      ++linkto->size;
      linkto = linkto->parent;
    }
    root = newnode->Splay();
  }

  void Delete(int key) {
    if (root == nullptr) {
      return;
    }

    Node* deleteto = root->Find(key);

    if (deleteto->key != key) {
      return;
    }

    deleteto->Splay();
    root = deleteto;
    if (deleteto->left == nullptr && deleteto->right == nullptr) {
      delete deleteto;
      root = nullptr;
    } else if (deleteto->left == nullptr) {
      root = deleteto->right;
      deleteto->right = nullptr;
      root->parent = nullptr;
      delete deleteto;
    } else if (deleteto->right == nullptr) {
      root = deleteto->left;
      deleteto->left = nullptr;
      root->parent = nullptr;
      delete deleteto;
    } else {
      --deleteto->size;
      Node* newroot = deleteto->left;
      --newroot->size;
      while (newroot->right != nullptr) {
        newroot = newroot->right;
        --newroot->size;
      }
      std::swap(newroot->key, deleteto->key);
      (newroot == newroot->parent->left ? newroot->parent->left
                                        : newroot->parent->right) =
          newroot->left;
      if (newroot->left != nullptr) {
        newroot->left->parent = newroot->parent;
      }
      newroot->left = newroot->right = newroot->parent = nullptr;
      delete newroot;
    }
  }

  bool Exists(int key) {
    if (root == nullptr) {
      return false;
    }
    root = root->Find(key)->Splay();
    return root->key == key;
  }

  int Next(int key) {
    Node* cur = root;
    Node* res = nullptr;
    while (cur != nullptr) {
      if (cur->key > key) {
        res = cur;
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    if (res == nullptr) {
      return -1;
    }
    root = res->Splay();
    return res->key;
  }

  int Prev(int key) {
    Node* cur = root;
    Node* res = nullptr;
    while (cur != nullptr) {
      if (cur->key < key) {
        res = cur;
        cur = cur->right;
      } else {
        cur = cur->left;
      }
    }
    if (res == nullptr) {
      return -1;
    }
    root = res->Splay();
    return res->key;
  }

  int Kth(int kk) {
    Node* cur = root;
    while (cur != nullptr) {
      int left_size = (cur->left == nullptr ? 0 : cur->left->size);
      if (left_size >= kk) {
        cur = cur->left;
      } else if (left_size == kk - 1) {
        root = cur->Splay();
        return cur->key;
      } else {
        cur = cur->right;
        kk -= left_size + 1;
      }
    }
    return -1;
  }
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();
  SplayTree tt;
  std::string ss;

  int xx;
  while (std::cin >> ss) {
    std::cin >> xx;
    if (ss[0] == 'i') {
      tt.Insert(xx);
    } else if (ss[0] == 'd') {
      tt.Delete(xx);
    } else if (ss[0] == 'e') {
      std::cout << std::boolalpha << tt.Exists(xx) << '\n';
    } else if (ss[0] == 'n') {
      int res = tt.Next(xx);
      if (res == -1) {
        std::cout << "none\n";
      } else {
        std::cout << res << '\n';
      }
    } else if (ss[0] == 'p') {
      int res = tt.Prev(xx);
      if (res == -1) {
        std::cout << "none\n";
      } else {
        std::cout << res << '\n';
      }
    } else if (ss[0] == 'k') {
      int res = tt.Kth(++xx);
      if (res == -1) {
        std::cout << "none\n";
      } else {
        std::cout << res << '\n';
      }
    }
  }
}