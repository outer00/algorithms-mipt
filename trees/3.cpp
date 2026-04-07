#include "algorithm"
#include "iostream"
#include "vector"

struct Node {
  void Update(long long value, long long pos);
  Node(long long tl, long long tr) : tl(tl), tr(tr), sum(0){};
  long long GetSum(long long pos) const;
  long long tl;
  long long tr;
  long long sum;
  Node* left_child = nullptr;
  Node* right_child = nullptr;
};

void Node::Update(long long value, long long pos) {
  sum += value;
  if (tl == tr) {
    return;
  }
  long long tm = (tl + tr) / 2;
  if (left_child == nullptr) {
    left_child = new Node(tl, tm);
  }
  if (right_child == nullptr) {
    right_child = new Node(tm + 1, tr);
  }
  if (pos <= tm) {
    left_child->Update(value, pos);
  }
  if (pos > tm) {
    right_child->Update(value, pos);
  }
}

long long Node::GetSum(long long pos) const {
  long long tm = (tl + tr) / 2;
  if (tl > pos) {
    return 0;
  }
  if (tr <= pos) {
    return sum;
  }
  if (tm <= pos) {
    if (left_child != nullptr && right_child != nullptr) {
      return left_child->sum + right_child->GetSum(pos);
    }
  }
  if (tm > pos) {
    if (left_child != nullptr) {
      return left_child->GetSum(pos);
    }
  }
  return 0;
}

long long BinSearch(const std::vector<long long>& coords, long long left,
                    long long right, long long coord) {
  if ((right - left) <= 1) {
    if (coords[left] == coord) {
      return left;
    }
    return right;
  }
  long long mid = (left + right) / 2;
  if (coords[mid] == coord) {
    return mid;
  }
  if (coords[mid] > coord) {
    return BinSearch(coords, left, mid, coord);
  }
  return BinSearch(coords, mid, right, coord);
}
void Del(Node& to_delete) {
  if (to_delete.tl == to_delete.tr) {
    return;
  }
  if (to_delete.left_child != nullptr) {
    Del(*to_delete.left_child);
    delete to_delete.left_child;
  }
  if (to_delete.right_child != nullptr) {
    Del(*to_delete.right_child);
    delete to_delete.right_child;
  }
}
int main() {
  long long qq;
  std::cin >> qq;
  std::vector<long long> coords;
  std::vector<long long> uniq_cords;
  std::vector<std::pair<char, long long>> querries(qq);
  for (long long i = 0; i < qq; ++i) {
    std::cin >> querries[i].first;
    std::cin >> querries[i].second;
    coords.push_back(querries[i].second);
  }
  std::sort(coords.begin(), coords.end());
  uniq_cords.push_back(coords[0]);
  for (size_t i = 1; i < coords.size(); ++i) {
    if (coords[i] != coords[i - 1]) {
      uniq_cords.push_back(coords[i]);
    }
  }
  long long ind;
  Node s_t(0, static_cast<long long>(uniq_cords.size()) - 1);
  for (long long i = 0; i < qq; ++i) {
    ind =
        BinSearch(uniq_cords, 0, static_cast<long long>(uniq_cords.size() - 1),
                  querries[i].second);
    if (querries[i].first == '+') {
      s_t.Update(querries[i].second, ind);
    } else {
      std::cout << s_t.GetSum(ind) << '\n';
    }
  }
  Del(s_t);
  return 0;
}