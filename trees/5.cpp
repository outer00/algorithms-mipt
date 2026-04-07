#include "iostream"
#include "vector"

struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int key;
  int value;
  Node(int key, int value) : key(key), value(value) {}
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();
  int n;
  int key;
  int value;
  std::cin >> n;
  std::vector<Node*> decart(n);
  std::cin >> key >> value;
  decart[0] = new Node(1, value);
  for (int i = 1; i < n; ++i) {
    std::cin >> key >> value;
    decart[i] = new Node(i + 1, value);

    Node* temp = decart[i - 1];
    while (temp->value > value && temp->parent != nullptr) {
      temp = temp->parent;
    }
    if (temp->value > value) {
      temp->parent = decart[i];
      decart[i]->left = temp;
    } else if (temp->right == nullptr) {
      temp->right = decart[i];
      decart[i]->parent = temp;
    } else {
      decart[i]->left = temp->right;
      temp->right->parent = decart[i];
      temp->right = decart[i];
      decart[i]->parent = temp;
    }
  }
  std::cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    int parent = (decart[i]->parent == nullptr ? 0 : decart[i]->parent->key);
    int left = (decart[i]->left == nullptr ? 0 : decart[i]->left->key);
    int right = (decart[i]->right == nullptr ? 0 : decart[i]->right->key);
    std::cout << parent << ' ' << left << ' ' << right << '\n';
  }
  for (int i = 0; i < n; ++i) {
    delete decart[i];
  }
}
