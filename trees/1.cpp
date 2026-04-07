#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Структура узла дерева отрезков
struct Node {
    long long count = 0; // Количество пользователей
    long long left = 0;  // Левая граница отрезка (номер страницы)
    long long right = 0; // Правая граница отрезка (номер страницы)
};

struct SegmentTree {
    static const long long kLeafCount = 65536;
    std::vector<Node> tree;

    SegmentTree() {
        tree.resize(kLeafCount * 2 + 1);
    }

    void Build() {
        // Инициализация листьев
        for (long long i = kLeafCount; i < kLeafCount * 2 + 1; ++i) {
            tree[i].count = 0;
            tree[i].left = i - kLeafCount;
            tree[i].right = tree[i].left;
        }
        // Инициализация внутренних узлов
        for (long long i = kLeafCount - 1; i >= 0; --i) {
            tree[i].count = 0;
            tree[i].left = tree[2 * i + 1].left;
            tree[i].right = tree[2 * i + 2].right;
        }
    }

    void Up(long long ind, long long delta) {
        tree[ind].count += delta;
        if (ind == 0) {
            return;
        }
        Up((ind - 1) / 2, delta);
    }

    void Insert(long long page, long long delta = 1) {
        long long ind = kLeafCount + page;
        tree[ind].count += delta;
        Up((ind - 1) / 2, delta);
    }

    void UpdateUser(long long prev_page, long long new_page) {
        Insert(prev_page, -1);
        Insert(new_page, 1);
    }

    long long GetPrefixSum(long long ind, long long target_page) {
        if (tree[2 * ind + 1].right == target_page) {
            return tree[2 * ind + 1].count;
        }
        if (tree[2 * ind + 1].right > target_page) {
            return GetPrefixSum(ind * 2 + 1, target_page);
        }
        if (tree[2 * ind + 1].right < target_page) {
            return tree[2 * ind + 1].count + GetPrefixSum(ind * 2 + 2, target_page);
        }
        return 0;
    }

    long long GetCount(long long target_page) {
        return GetPrefixSum(0, target_page);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const long long kMaxUsers = 100001;
    const int kPrecision = 6;

    long long num_queries;
    if (!(std::cin >> num_queries)) return 0;

    std::string command;
    long long user_id;
    long long page;
    long long active_users_count = 0;

    std::vector<long long> user_pages(kMaxUsers, 0);

    SegmentTree page_tree;
    page_tree.Build();

    for (long long i = 0; i < num_queries; ++i) {
        std::cin >> command;

        if (command == "RUN") {
            std::cin >> user_id >> page;
            if (user_pages[user_id] == 0) {
                ++active_users_count;
                page_tree.Insert(page);
            } else {
                page_tree.UpdateUser(user_pages[user_id], page);
            }
            user_pages[user_id] = page;
        }
        else if (command == "CHEER") {
            std::cin >> user_id;
            if (user_pages[user_id] == 0) {
                std::cout << 0 << '\n';
            } else {
                if (active_users_count == 1) {
                    std::cout << 1 << '\n';
                } else {
                    long double result = static_cast<long double>(page_tree.GetCount(user_pages[user_id] - 1)) / (active_users_count - 1);
                    std::cout << std::fixed << std::setprecision(kPrecision) << result << '\n';
                }
            }
        }
    }

    return 0;
}