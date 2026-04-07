#include <iostream>
#include <vector>
#define range(i, a, b) for (int i = a; i <= b; ++i)

struct Data {
  std::vector<std::vector<int>> matrix;
  std::vector<int> temp;
  std::vector<bool> in_use;
  explicit Data(int lnum)
      : matrix(lnum + 1), temp(lnum + 1, -1), in_use(lnum + 1, false) {}
  bool Hurb(int vv) {
    if (in_use[vv]) {
      return false;
    }
    in_use[vv] = true;
    for (size_t i = 0; i < matrix[vv].size(); ++i) {
      if (temp[matrix[vv][i]] == -1 || Hurb(temp[matrix[vv][i]])) {
        temp[matrix[vv][i]] = vv;
        return true;
      }
    }
    return false;
  }
  void Getans(int vv) {
    Hurb(vv);
    in_use.assign(in_use.size(), false);
  }
};

int main() {
  int answer = 0;
  int ll;
  int rr;
  std::cin >> ll >> rr;
  Data bruh(ll);
  int from;
  int to;
  range(i, 1, rr) {
    std::cin >> from >> to;
    bruh.matrix[from].emplace_back(to);
  }
  range(i, 1, ll) { bruh.Getans(i); }
  range(i, 1, ll) {
    if (bruh.temp[i] == -1) {
      ++answer;
    }
  }
  std::cout << answer;
  return 0;
}