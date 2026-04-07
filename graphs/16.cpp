#include <iostream>
#include <vector>

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();
  int num;
  int val;
  std::cin >> num;
  std::vector<std::vector<bool>> matrix(num, std::vector<bool>(num));
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      std::cin >> val;
      matrix[i][j] = val == 1;
    }
  }
  for (int k = 0; k < num; ++k) {
    for (int i = 0; i < num; ++i) {
      for (int j = 0; j < num; ++j) {
        matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
      }
    }
  }
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      std::cout << (matrix[i][j] ? "1 " : "0 ");
    }
    std::cout << '\n';
  }
}