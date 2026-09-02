#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

struct QueueWithMax {
  std::deque<long long> deq;

  long long GetMax() const { return deq.front(); }

  void Push(long long element) {
    while (!deq.empty() && deq.back() < element) {
      deq.pop_back();
    }
    deq.push_back(element);
  }

  void Pop(long long removed_element) {
    if (!deq.empty() && deq.front() == removed_element) {
      deq.pop_front();
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int count;
  if (!(std::cin >> count)) {
    return 0;
  }

  std::vector<long long> elements(count);
  long long total_sum = 0;
  for (int i = 0; i < count; ++i) {
    std::cin >> elements[i];
    total_sum += elements[i];
  }

  int second_arc = count / 2;
  int first_arc = second_arc + count % 2;

  std::vector<long long> arc_sums(count, 0);
  for (int i = 0; i < second_arc; ++i) {
    arc_sums[0] += elements[i];
  }
  for (int i = 1; i < count; ++i) {
    arc_sums[i] = arc_sums[i - 1] - elements[i - 1] +
                  elements[(i - 1 + second_arc) % count];
  }

  QueueWithMax max_queue;
  for (int i = 0; i < first_arc; ++i) {
    max_queue.Push(arc_sums[i]);
  }

  long long second_score = max_queue.GetMax();
  for (int i = 1; i < count; ++i) {
    max_queue.Pop(arc_sums[i - 1]);
    max_queue.Push(arc_sums[(i - 1 + first_arc) % count]);
    second_score = std::min(second_score, max_queue.GetMax());
  }

  std::cout << total_sum - second_score << " " << second_score << "\n";
  return 0;
}
