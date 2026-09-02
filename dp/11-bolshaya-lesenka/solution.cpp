#include <climits>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int count;
  std::cin >> count;
  std::vector<int> values(count);
  for (int i = 0; i < count; ++i) {
    std::cin >> values[i];
  }

  std::vector<int> ends_up(count, INT_MAX);
  std::vector<int> ends_down(count, INT_MAX);
  ends_up[0] = ends_down[0] = values[0];

  int up_size = 1;
  int down_size = 1;

  for (int i = 1; i < count; ++i) {
    if (values[i] > values[i - 1]) {
      for (int j = up_size; j < down_size; ++j) {
        ends_up[j] = ends_down[j];
      }
      up_size = down_size;
      ends_up[up_size] = values[i];
      ++up_size;
    } else if (values[i] < values[i - 1]) {
      for (int j = down_size; j < up_size; ++j) {
        ends_down[j] = ends_up[j];
      }
      down_size = up_size;
      ends_down[down_size] = values[i];
      ++down_size;
    }
  }

  const std::vector<int>& answer = up_size > down_size ? ends_up : ends_down;
  int length = up_size > down_size ? up_size : down_size;

  std::cout << length << '\n';
  for (int i = 0; i < length; ++i) {
    std::cout << answer[i] << ' ';
  }
  return 0;
}
