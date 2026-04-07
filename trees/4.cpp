#include "iostream"
#include "string"
#include "vector"

int Fn(int xx) { return xx & (xx + 1); }

int Gn(int xx) { return xx | (xx + 1); }

void Update(std::vector<std::vector<int>>& sum, int xx, int yy, int num) {
  for (int i = xx; i < num; i = Gn(i)) {
    for (int j = yy; j < num; j = Gn(j)) {
      ++sum[i][j];
    }
  }
}

int GetPrefSum(std::vector<std::vector<int>>& sum, int left, int right) {
  if (left < 0 || right < 0) {
    return 0;
  }
  int ans = 0;
  for (int i = left; i >= 0; i = Fn(i) - 1) {
    for (int j = right; j >= 0; j = Fn(j) - 1) {
      ans += sum[i][j];
    }
  }
  return ans;
}

int GetSum(std::vector<std::vector<int>>& sum, int x1, int y1, int x2, int y2) {
  int max_x = std::max(x1, x2);
  int min_x = std::min(x1, x2);
  int max_y = std::max(y1, y2);
  int min_y = std::min(y1, y2);
  return GetPrefSum(sum, max_x, max_y) - GetPrefSum(sum, max_x, min_y - 1) -
         GetPrefSum(sum, min_x - 1, max_y) +
         GetPrefSum(sum, min_x - 1, min_y - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num;
  int quer;
  std::cin >> num >> quer;
  std::vector<std::vector<int>> sum(num, std::vector<int>(num, 0));
  std::string command;
  int first;
  int sec;
  int third;
  int fourth;
  for (int i = 0; i < quer; ++i) {
    std::cin >> command;
    if (command == "ADD") {
      std::cin >> first >> sec;
      --first;
      --sec;
      Update(sum, first, sec, num);
    } else {
      std::cin >> first >> sec >> third >> fourth;
      --first;
      --sec;
      --third;
      --fourth;
      std::cout << GetSum(sum, first, sec, third, fourth) << '\n';
    }
  }
}