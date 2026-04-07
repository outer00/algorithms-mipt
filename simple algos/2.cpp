#include <deque>
#include <iostream>
#include <vector>

// comments by gemini AI

struct QueueWithMax {
    std::deque<long long> deq;

    long long GetMax() const {
        return deq.front();
    }

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
    // Ускоряем ввод-вывод
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_elements;
    if (!(std::cin >> num_elements)) return 0;

    std::vector<long long> elements(num_elements);
    long long total_sum = 0;

    for (int i = 0; i < num_elements; i++) {
        std::cin >> elements[i];
        total_sum += elements[i];
    }

    // Размеры окон
    int half_size = num_elements / 2;
    int window_size = half_size + (num_elements % 2);

    // Массив префиксных/скользящих сумм для размера half_size
    std::vector<long long> half_sums(num_elements, 0);
    for (int i = 0; i < half_size; i++) {
        half_sums[0] += elements[i];
    }

    // Заполняем остальные суммы, двигаясь по кругу
    for (int i = 1; i < num_elements; i++) {
        half_sums[i] = half_sums[i - 1] - elements[i - 1] + elements[(i - 1 + half_size) % num_elements];
    }

    QueueWithMax max_queue;

    // Инициализируем очередь первым окном размера window_size
    for (int i = 0; i < window_size; i++) {
        max_queue.Push(half_sums[i]);
    }

    long long min_max_sum = max_queue.GetMax();

    // Сдвигаем окно и ищем минимальное значение из максимальных
    for (int i = 1; i < num_elements; i++) {
        max_queue.Pop(half_sums[i - 1]);
        max_queue.Push(half_sums[(i - 1 + window_size) % num_elements]);

        long long current_max = max_queue.GetMax();
        if (current_max < min_max_sum) {
            min_max_sum = current_max;
        }
    }

    std::cout << total_sum - min_max_sum << " " << min_max_sum << "\n";

    return 0;
}