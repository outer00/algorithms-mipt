#include <iostream>
#include <string>

struct SplayTree {
  struct Node {
    int key, size;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int key) : key(key), size(1) {}

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
      size = parent->size;
      if (right != nullptr) {
        parent->size -= right->size;
      }
      --parent->size;
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
      size = parent->size;
      if (left != nullptr) {
        parent->size -= left->size;
      }
      --parent->size;
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
    Node* place = root->Find(key);
    if (place == nullptr || place->key == key) {
      return;
    }
    Node* new_node =
        (key < place->key ? place->AddLeft(key) : place->AddRight(key));
    while (place != nullptr) {
      ++place->size;
      place = place->parent;
    }
    root = new_node->Splay();
  }

  void Delete(int key) {
    if (root == nullptr) {
      return;
    }

    Node* target = root->Find(key);

    if (target->key != key) {
      return;
    }

    target->Splay();
    root = target;
    if (target->left == nullptr && target->right == nullptr) {
      delete target;
      root = nullptr;
    } else if (target->left == nullptr) {
      root = target->right;
      target->right = nullptr;
      root->parent = nullptr;
      delete target;
    } else if (target->right == nullptr) {
      root = target->left;
      target->left = nullptr;
      root->parent = nullptr;
      delete target;
    } else {
      --target->size;
      Node* new_root = target->left;
      --new_root->size;
      while (new_root->right != nullptr) {
        new_root = new_root->right;
        --new_root->size;
      }
      std::swap(new_root->key, target->key);
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

  bool Exists(int key) {
    if (root == nullptr) {
      return false;
    }
    root = root->Find(key)->Splay();
    return root->key == key;
  }

  int Next(int key) {
    Node* current = root;
    Node* result = nullptr;
    while (current != nullptr) {
      if (current->key > key) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (result == nullptr) {
      return -1;
    }
    root = result->Splay();
    return result->key;
  }

  int Prev(int key) {
    Node* current = root;
    Node* result = nullptr;
    while (current != nullptr) {
      if (current->key < key) {
        result = current;
        current = current->right;
      } else {
        current = current->left;
      }
    }
    if (result == nullptr) {
      return -1;
    }
    root = result->Splay();
    return result->key;
  }

  int Kth(int key) {
    Node* current = root;
    while (current != nullptr) {
      int left_size = (current->left == nullptr ? 0 : current->left->size);
      if (left_size >= key) {
        current = current->left;
      } else if (left_size == key - 1) {
        root = current->Splay();
        return current->key;
      } else {
        current = current->right;
        key -= left_size + 1;
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
  SplayTree tree;
  std::string command;

  int value;
  while (std::cin >> command) {
    std::cin >> value;
    if (command[0] == 'i') {
      tree.Insert(value);
    } else if (command[0] == 'd') {
      tree.Delete(value);
    } else if (command[0] == 'e') {
      std::cout << std::boolalpha << tree.Exists(value) << '\n';
    } else if (command[0] == 'n') {
      int result = tree.Next(value);
      if (result == -1) {
        std::cout << "none\n";
      } else {
        std::cout << result << '\n';
      }
    } else if (command[0] == 'p') {
      int result = tree.Prev(value);
      if (result == -1) {
        std::cout << "none\n";
      } else {
        std::cout << result << '\n';
      }
    } else if (command[0] == 'k') {
      int result = tree.Kth(++value);
      if (result == -1) {
        std::cout << "none\n";
      } else {
        std::cout << result << '\n';
      }
    }
  }
}