#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int count;
  std::cin >> count;

  std::vector<long long> neighbors(count, 0);
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < count; ++j) {
      char cell;
      std::cin >> cell;
      if (cell == '1') {
        neighbors[i] |= 1LL << j;
      }
    }
    neighbors[i] |= 1LL << i;
  }

  int left_size = count / 2;
  int right_size = count - left_size;
  int left_masks = 1 << left_size;
  int right_masks = 1 << right_size;

  long long answer = 1;

  std::vector<int> left_common(left_masks, 0);
  std::vector<int> subclique_count(left_masks, 0);
  left_common[0] = (1 << left_size) - 1;
  subclique_count[0] = 1;

  int bit = -1;
  for (int mask = 1; mask < left_masks; ++mask) {
    if ((mask & (mask - 1)) == 0) {
      ++bit;
    }
    left_common[mask] =
        left_common[mask ^ (1 << bit)] &
        static_cast<int>(neighbors[bit] & ((1LL << left_size) - 1));
    if ((mask | left_common[mask]) != left_common[mask]) {
      continue;
    }
    ++answer;
    subclique_count[mask] = 1;
  }

  for (int position = 0; position < left_size; ++position) {
    for (int mask = 0; mask < left_masks; ++mask) {
      if ((mask & (1 << position)) == 0) {
        subclique_count[mask | (1 << position)] += subclique_count[mask];
      }
    }
  }

  std::vector<int> right_common(right_masks, 0);
  right_common[0] = (1 << right_size) - 1;
  left_common.resize(right_masks);
  left_common[0] = (1 << left_size) - 1;

  bit = -1;
  for (int mask = 1; mask < right_masks; ++mask) {
    if ((mask & (mask - 1)) == 0) {
      ++bit;
    }
    int previous = mask ^ (1 << bit);
    right_common[mask] =
        right_common[previous] &
        static_cast<int>((neighbors[bit + left_size] >> left_size) &
                         ((1LL << right_size) - 1));
    left_common[mask] =
        left_common[previous] &
        static_cast<int>(neighbors[bit + left_size] & ((1LL << left_size) - 1));
    if ((mask | right_common[mask]) != right_common[mask]) {
      continue;
    }
    answer += subclique_count[left_common[mask]];
  }

  std::cout << answer;
  return 0;
}
