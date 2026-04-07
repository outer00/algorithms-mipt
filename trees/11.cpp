#include <iostream>
#include <vector>

struct Treap {
  struct Node {
    int key, subtree_size;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int key) : key(key), subtree_size(1) {}

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
      int leftsz = (left == nullptr ? 0 : left->subtree_size);
      int rightsz = (right == nullptr ? 0 : right->subtree_size);
      int cnt = subtree_size - leftsz - rightsz;
      subtree_size = parent->subtree_size;
      parent->subtree_size -= rightsz;

      parent->subtree_size -= cnt;
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
      int leftsz = (left == nullptr ? 0 : left->subtree_size);
      int rightsz = (right == nullptr ? 0 : right->subtree_size);
      int cnt = subtree_size - leftsz - rightsz;
      subtree_size = parent->subtree_size;
      parent->subtree_size -= leftsz;
      parent->subtree_size -= cnt;
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
    if (linkto == nullptr) {
      return;
    }
    if (linkto->key == key) {
      root = linkto->Splay();
      ++linkto->subtree_size;
      return;
    }
    Node* newnode =
        (key < linkto->key ? linkto->AddLeft(key) : linkto->AddRight(key));
    while (linkto != nullptr) {
      ++linkto->subtree_size;
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

    root = deleteto->Splay();

    int leftsz = (deleteto->left == nullptr ? 0 : deleteto->left->subtree_size);
    int rightsz =
        (deleteto->right == nullptr ? 0 : deleteto->right->subtree_size);
    if ((deleteto->subtree_size - leftsz - rightsz) > 1) {
      --deleteto->subtree_size;
      return;
    }

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
      --deleteto->subtree_size;
      Node* newroot = deleteto->left;
      --newroot->subtree_size;
      while (newroot->right != nullptr) {
        newroot = newroot->right;
        --newroot->subtree_size;
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

  int LessCnt(int val) {
    if (root == nullptr) {
      return 0;
    }
    root = root->Find(val)->Splay();

    if (root->key < val) {
      int rightsz = (root->right == nullptr ? 0 : root->right->subtree_size);
      return root->subtree_size - rightsz;
    }
    return (root->left == nullptr ? 0 : root->left->subtree_size);
  }

  int SegmentCnt(int x, int y) {
    int a = LessCnt(x);
    int b = LessCnt(y + 1);
    return b - a;
  }
};

void CopyAndInsert(Treap::Node* node, Treap& result) {
  if (node == nullptr) {
    return;
  }
  int leftsz = (node->left == nullptr ? 0 : node->left->subtree_size);
  int rightsz = (node->right == nullptr ? 0 : node->right->subtree_size);
  int n = node->subtree_size - leftsz - rightsz;
  for (int i = 0; i < n; ++i) {
    result.Insert(node->key);
  }
  CopyAndInsert(node->left, result);
  CopyAndInsert(node->right, result);
}

void Merge(Treap& t, const Treap& t1, const Treap& t2) {
  CopyAndInsert(t1.root, t);
  CopyAndInsert(t2.root, t);
}

class SegmentTree {
 private:
  int n_;
  std::vector<Treap> tree_;
  std::vector<int> arr_;

  void Build(int node, int start, int end) {
    if (start == end) {
      tree_[node].Insert(arr_[start]);
    } else {
      int mid = (start + end) / 2;
      Build(2 * node + 1, start, mid);
      Build(2 * node + 2, mid + 1, end);
      Merge(tree_[node], tree_[2 * node + 1], tree_[2 * node + 2]);
    }
  }

  void Update(int node, int start, int end, int idx, int value) {
    if (start == end) {
      // Листовой узел
      tree_[node].Delete(arr_[idx]);
      tree_[node].Insert(value);
      arr_[idx] = value;
    } else {
      int deleteto = arr_[idx];
      int mid = (start + end) / 2;
      if (start <= idx && idx <= mid) {
        Update(2 * node + 1, start, mid, idx, value);
      } else {
        Update(2 * node + 2, mid + 1, end, idx, value);
      }
      tree_[node].Delete(deleteto);
      tree_[node].Insert(value);
      arr_[idx] = value;
    }
  }

  int Query(int node, int start, int end, int l, int r,
            std::pair<int, int> xy) {
    if (r < start || end < l) {
      return 0;
    }
    if (l <= start && end <= r) {
      return tree_[node].SegmentCnt(xy.first, xy.second);
    }
    int mid = (start + end) / 2;
    int left_sum = Query(2 * node + 1, start, mid, l, r, xy);
    int right_sum = Query(2 * node + 2, mid + 1, end, l, r, xy);
    return left_sum + right_sum;
  }

 public:
  SegmentTree(const std::vector<int>& input_arr)
      : n_((int)input_arr.size()), tree_(4 * n_), arr_(input_arr) {
    Build(0, 0, n_ - 1);
  }

  void Update(int idx, int value) { Update(0, 0, n_ - 1, idx, value); }

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
  int n;
  int q;
  std::cin >> n >> q;
  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  SegmentTree segt(arr);
  for (int i = 0; i < q; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "GET") {
      int l;
      int r;
      int x;
      int y;
      std::cin >> l >> r >> x >> y;
      std::cout << segt.Query(--l, --r, x, y) << '\n';
    } else {
      int ind;
      int x;
      std::cin >> ind >> x;
      segt.Update(--ind, x);
    }
  }
}
