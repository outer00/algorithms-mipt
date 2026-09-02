#include <iostream>
#include <vector>

struct Node {
  Node(int key, int value) : key(key), value(value) {}

  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int key;
  int value;
};

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  int size;
  std::cin >> size;

  std::vector<Node*> nodes(size);
  int key;
  int value;
  std::cin >> key >> value;
  nodes[0] = new Node(1, value);

  for (int i = 1; i < size; ++i) {
    std::cin >> key >> value;
    nodes[i] = new Node(i + 1, value);

    Node* current = nodes[i - 1];
    while (current->value > value && current->parent != nullptr) {
      current = current->parent;
    }
    if (current->value > value) {
      current->parent = nodes[i];
      nodes[i]->left = current;
    } else if (current->right == nullptr) {
      current->right = nodes[i];
      nodes[i]->parent = current;
    } else {
      nodes[i]->left = current->right;
      current->right->parent = nodes[i];
      current->right = nodes[i];
      nodes[i]->parent = current;
    }
  }

  std::cout << "YES\n";
  for (int i = 0; i < size; ++i) {
    int parent = nodes[i]->parent == nullptr ? 0 : nodes[i]->parent->key;
    int left = nodes[i]->left == nullptr ? 0 : nodes[i]->left->key;
    int right = nodes[i]->right == nullptr ? 0 : nodes[i]->right->key;
    std::cout << parent << ' ' << left << ' ' << right << '\n';
  }

  for (int i = 0; i < size; ++i) {
    delete nodes[i];
  }
  return 0;
}
