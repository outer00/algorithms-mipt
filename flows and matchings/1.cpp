#include <iostream>
#include <vector>
#define range(i, a, b) for (int i = a; i <= b; ++i)

struct Data {
  std::vector<std::vector<int>> matrix;
  std::vector<int> temp;
  std::vector<bool> in_use;
  Data(int lnum, int rnum)
      : matrix(lnum + 1), temp(rnum + 1, -1), in_use(lnum + 1, false) {}
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
  Data bruh(ll, rr);
  int bro;
  int ii = 0;
  while (ii < ll) {
    ++ii;
    std::cin >> bro;
    while (bro != 0) {
      bruh.matrix[ii].emplace_back(bro);
      std::cin >> bro;
    }
  }
  range(i, 1, ll) { bruh.Getans(i); }
  range(i, 1, rr) {
    if (bruh.temp[i] != -1) {
      ++answer;
    }
  }
  std::cout << answer << '\n';
  range(i, 1, rr) {
    if (bruh.temp[i] != -1) {
      std::cout << bruh.temp[i] << ' ' << i << '\n';
    }
  }
  return 0;
}