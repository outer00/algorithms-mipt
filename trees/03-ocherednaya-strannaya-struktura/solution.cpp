#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  Node(long long left, long long right) : left(left), right(right), sum(0) {}

  void Update(long long value, long long position);
  long long GetPrefixSum(long long position) const;

  long long left;
  long long right;
  long long sum;
  Node* left_child = nullptr;
  Node* right_child = nullptr;
};

void Node::Update(long long value, long long position) {
  sum += value;
  if (left == right) {
    return;
  }
  long long middle = (left + right) / 2;
  if (left_child == nullptr) {
    left_child = new Node(left, middle);
  }
  if (right_child == nullptr) {
    right_child = new Node(middle + 1, right);
  }
  if (position <= middle) {
    left_child->Update(value, position);
  } else {
    right_child->Update(value, position);
  }
}

long long Node::GetPrefixSum(long long position) const {
  if (left > position) {
    return 0;
  }
  if (right <= position) {
    return sum;
  }
  long long middle = (left + right) / 2;
  if (middle <= position) {
    if (left_child != nullptr && right_child != nullptr) {
      return left_child->sum + right_child->GetPrefixSum(position);
    }
  } else if (left_child != nullptr) {
    return left_child->GetPrefixSum(position);
  }
  return 0;
}

void DeleteSubtree(Node& node) {
  if (node.left_child != nullptr) {
    DeleteSubtree(*node.left_child);
    delete node.left_child;
  }
  if (node.right_child != nullptr) {
    DeleteSubtree(*node.right_child);
    delete node.right_child;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long query_count;
  std::cin >> query_count;

  std::vector<std::pair<char, long long>> queries(query_count);
  std::vector<long long> values;
  values.reserve(query_count);
  for (long long i = 0; i < query_count; ++i) {
    std::cin >> queries[i].first >> queries[i].second;
    values.push_back(queries[i].second);
  }

  std::sort(values.begin(), values.end());
  values.erase(std::unique(values.begin(), values.end()), values.end());

  Node tree(0, static_cast<long long>(values.size()) - 1);
  for (const auto& [command, value] : queries) {
    long long index =
        std::lower_bound(values.begin(), values.end(), value) - values.begin();
    if (command == '+') {
      tree.Update(value, index);
    } else {
      std::cout << tree.GetPrefixSum(index) << '\n';
    }
  }

  DeleteSubtree(tree);
  return 0;
}
