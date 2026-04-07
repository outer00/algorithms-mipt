#include <deque>
#include <iostream>
#include <vector>

// comments by gemini AI

// Структура для хранения значения ячейки и её оригинальных координат
struct Cell {
    int value;
    int x;
    int y;
    int z;
};

// Структура для хранения итоговых координат (ответа)
struct Position {
    int x;
    int y;
    int z;
};

using Grid3DInt = std::vector<std::vector<std::vector<int>>>;
using Grid3DCell = std::vector<std::vector<std::vector<Cell>>>;
using Grid3DPos = std::vector<std::vector<std::vector<Position>>>;

// Глобальные переменные (размеры сетки и окна)
int size_x, size_y, size_z;
int win_x, win_y, win_z;
int queries, cur_i, cur_j, cur_k;

struct QueueWithMax {
    std::deque<Cell> deq;

    Cell GetMax() const { 
        return deq.front(); 
    }

    void Push(const Cell& element) {
        while (!deq.empty() && deq.back().value < element.value) {
            deq.pop_back();
        }
        deq.push_back(element);
    }

    void Pop(const Cell& removed_element) {
        if (!deq.empty() && deq.front().value == removed_element.value) {
            deq.pop_front();
        }
    }
};

void FillGrid(Grid3DInt& grid) {
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            for (int k = 0; k < size_z; k++) {
                std::cin >> grid[i][j][k];
            }
        }
    }
}

// Проход скользящим окном вдоль оси Z
void SlidingWindowZ(const Grid3DInt& grid, Grid3DCell& max_z_pass) {
    Cell temp;
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            QueueWithMax quemax;
            for (int k = 0; k < size_z + win_z - 1; k++) {
                if (k < win_z) {
                    temp = {grid[i][j][k], i, j, k};
                    quemax.Push(temp);
                    if (max_z_pass[i][j][0].value < quemax.GetMax().value) {
                        max_z_pass[i][j][0] = quemax.GetMax();
                    }
                } else if (k < size_z) {
                    temp = {grid[i][j][k - win_z], i, j, k - win_z};
                    quemax.Pop(temp);
                    
                    temp = {grid[i][j][k], i, j, k};
                    quemax.Push(temp);
                    
                    max_z_pass[i][j][k - win_z + 1] = quemax.GetMax();
                } else {
                    temp = {grid[i][j][k - win_z], i, j, k - win_z};
                    quemax.Pop(temp);
                    
                    max_z_pass[i][j][k - win_z + 1] = quemax.GetMax();
                }
            }
        }
    }
}

// Проход скользящим окном вдоль оси Y на основе результатов оси Z
void SlidingWindowY(const Grid3DCell& max_z_pass, Grid3DCell& max_yz_pass) {
    Cell temp;
    for (int i = 0; i < size_x; i++) {
        for (int k = 0; k < size_z; k++) {
            QueueWithMax quemax;
            for (int j = 0; j < size_y + win_y - 1; j++) {
                if (j < win_y) {
                    temp = max_z_pass[i][j][k];
                    quemax.Push(temp);
                    if (max_yz_pass[i][0][k].value < quemax.GetMax().value) {
                        max_yz_pass[i][0][k] = quemax.GetMax();
                    }
                } else if (j < size_y) {
                    temp = max_z_pass[i][j - win_y][k];
                    quemax.Pop(temp);
                    
                    temp = max_z_pass[i][j][k];
                    quemax.Push(temp);
                    
                    max_yz_pass[i][j - win_y + 1][k] = quemax.GetMax();
                } else {
                    temp = max_z_pass[i][j - win_y][k];
                    quemax.Pop(temp);
                    
                    max_yz_pass[i][j - win_y + 1][k] = quemax.GetMax();
                }
            }
        }
    }
}

// Проход скользящим окном вдоль оси X на основе результатов осей Y и Z
void SlidingWindowX(const Grid3DCell& max_yz_pass, Grid3DCell& max_xyz_pass) {
    Cell temp;
    for (int j = 0; j < size_y; j++) {
        for (int k = 0; k < size_z; k++) {
            QueueWithMax quemax;
            for (int i = 0; i < size_x + win_x - 1; i++) {
                if (i < win_x) {
                    temp = max_yz_pass[i][j][k];
                    quemax.Push(temp);
                    if (max_xyz_pass[0][j][k].value < quemax.GetMax().value) {
                        max_xyz_pass[0][j][k] = quemax.GetMax();
                    }
                } else if (i < size_x) {
                    temp = max_yz_pass[i - win_x][j][k];
                    quemax.Pop(temp);
                    
                    temp = max_yz_pass[i][j][k];
                    quemax.Push(temp);
                    
                    max_xyz_pass[i - win_x + 1][j][k] = quemax.GetMax();
                } else {
                    temp = max_yz_pass[i - win_x][j][k];
                    quemax.Pop(temp);
                    
                    max_xyz_pass[i - win_x + 1][j][k] = quemax.GetMax();
                }
            }
        }
    }
}

// Восстановление координат итоговых максимумов (сжатие путей)
void BuildPaths(Grid3DPos& answers, const Grid3DCell& max_xyz_pass, const Grid3DInt& grid) {
    for (int i = size_x - 1; i >= 0; i--) {
        for (int j = size_y - 1; j >= 0; j--) {
            for (int k = size_z - 1; k >= 0; k--) {
                const Cell& max_cell = max_xyz_pass[i][j][k];
                
                if (max_cell.value == grid[i][j][k]) {
                    answers[i][j][k] = {i, j, k};
                } else {
                    // Перенаправляем на координаты уже найденного максимума
                    answers[i][j][k] = answers[max_cell.x][max_cell.y][max_cell.z];
                }
            }
        }
    }
}

void ProcessQueries(const Grid3DPos& answers) {
    std::cin >> queries;
    for (int tt = 0; tt < queries; tt++) {
        std::cin >> cur_i >> cur_j >> cur_k;
        const Position& ans = answers[cur_i][cur_j][cur_k];
        std::cout << ans.x << " " << ans.y << " " << ans.z << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> size_x >> size_y >> size_z >> win_x >> win_y >> win_z;
    
    // Инициализация трехмерных сеток
    Grid3DInt grid(size_x, std::vector<std::vector<int>>(size_y, std::vector<int>(size_z)));
    
    // Изначально заполняем Cell фиктивными данными (0 для value, 0 для координат)
    Cell default_cell = {0, 0, 0, 0}; 
    Grid3DCell max_z_pass(size_x, std::vector<std::vector<Cell>>(size_y, std::vector<Cell>(size_z, default_cell)));
    Grid3DCell max_yz_pass(size_x, std::vector<std::vector<Cell>>(size_y, std::vector<Cell>(size_z, default_cell)));
    Grid3DCell max_xyz_pass(size_x, std::vector<std::vector<Cell>>(size_y, std::vector<Cell>(size_z, default_cell)));
    
    Grid3DPos answers(size_x, std::vector<std::vector<Position>>(size_y, std::vector<Position>(size_z)));
    
    FillGrid(grid);
    SlidingWindowZ(grid, max_z_pass);
    SlidingWindowY(max_z_pass, max_yz_pass);
    SlidingWindowX(max_yz_pass, max_xyz_pass);
    BuildPaths(answers, max_xyz_pass, grid);
    ProcessQueries(answers);
    
    return 0;
}