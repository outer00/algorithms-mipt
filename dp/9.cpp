#include <algorithm>
#include <iostream>
#include <vector>

void GetAns(const std::vector<int>& dp, const std::vector<int>& par) {
  std::cout << dp.size() << "\n";
  std::vector<int> ans(dp.size());
  int cur = dp.back();
  for (int i = static_cast<int>(dp.size()) - 1; i > -1; --i) {
    ans[i] = cur + 1;
    cur = par[cur];
  }
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  int num;
  std::cin >> num;
  std::vector<int> line(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> line[i];
  }
  std::vector<int> dp;
  std::vector<int> par(num, -1);
  dp.push_back(0);
  for (int i = 1; i < num; ++i) {
    auto it = std::lower_bound(dp.begin(), dp.end(), i, [&](int xx, int yy) {
      return line[xx] >= line[yy];
    });
    if (it != dp.end()) {
      par[i] = (it != dp.begin()) ? *(it - 1) : -1;
      *it = i;
    } else {
      par[i] = dp.back();
      dp.push_back(i);
    }
  }
  GetAns(dp, par);

  return 0;
}
