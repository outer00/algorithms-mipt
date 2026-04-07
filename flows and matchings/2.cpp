#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

bool Kuhn(std::vector<bool>& visited, std::vector<std::vector<int>>& mat,
          std::vector<int>& mt, int v) {
  if (visited[v]) {
    return false;
  }
  visited[v] = true;
  for (auto u : mat[v]) {
    if (mt[u] == -1 || Kuhn(visited, mat, mt, mt[u])) {
      mt[u] = v;
      return true;
    }
  }
  return false;
}

int GetInp(std::vector<std::vector<bool>>& mask,
           std::map<std::pair<int, int>, int>& ind, int num, int mnum) {
  int white;
  int black;
  int good;
  white = 0;
  black = 0;
  good = 0;
  std::string s;
  for (int i = 0; i < num; ++i) {
    std::cin >> s;
    for (int j = 0; j < mnum; ++j) {
      mask[i][j] = s[j] == '.';
      if ((i + j) % 2 != 0) {
        ++black;
        ind[{i, j}] = black;
      } else {
        ++white;
        ind[{i, j}] = white;
      }
      if (!mask[i][j]) {
        ++good;
      }
    }
  }
  return good;
}

auto Fill(std::vector<std::vector<bool>>& mask,
          std::map<std::pair<int, int>, int>& ind, int num, int mnum) {
  int left;
  left = (mnum * num + 1) / 2;
  std::vector<std::vector<int>> mat(left + 1);
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < mnum; ++j) {
      if (mask[i][j] || ((i + j) % 2) != 0) {
        continue;
      }
      if (i != 0) {
        if (!mask[i - 1][j]) {
          mat[ind[{i, j}]].push_back(ind[{i - 1, j}]);
        }
      }
      if (i != num - 1) {
        if (!mask[i + 1][j]) {
          mat[ind[{i, j}]].push_back(ind[{i + 1, j}]);
        }
      }
      if (j != 0) {
        if (!mask[i][j - 1]) {
          mat[ind[{i, j}]].push_back(ind[{i, j - 1}]);
        }
      }
      if (j != mnum - 1) {
        if (!mask[i][j + 1]) {
          mat[ind[{i, j}]].push_back(ind[{i, j + 1}]);
        }
      }
    }
  }
  return mat;
}

int main() {
  int num;
  int mnum;
  int cost1x1;
  int cost2x1;
  std::cin >> num >> mnum >> cost1x1 >> cost2x1;
  int left;
  int right;
  left = (mnum * num + 1) / 2;
  right = (mnum * num) / 2;
  std::vector<std::vector<bool>> mask(num, std::vector<bool>(mnum));
  std::map<std::pair<int, int>, int> ind;
  int good = GetInp(mask, ind, num, mnum);
  auto mat = Fill(mask, ind, num, mnum);
  std::vector<int> mt(right + 1, -1);
  for (int v = 1; v <= left; ++v) {
    std::vector<bool> visited(left + 1, false);
    Kuhn(visited, mat, mt, v);
  }
  int sum;
  int cnt;
  sum = 0;
  cnt = 0;
  for (int v = 1; v <= right; ++v) {
    if (mt[v] != -1) {
      sum += std::min(cost1x1, 2 * cost2x1);
      cnt += 2;
    }
  }
  std::cout << sum + (good - cnt) * cost2x1 << "\n";
  return 0;
}