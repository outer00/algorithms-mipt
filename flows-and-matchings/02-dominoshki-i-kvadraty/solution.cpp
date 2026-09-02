#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool Kuhn(std::vector<bool>& visited, std::vector<std::vector<int>>& adj,
          std::vector<int>& match, int v) {
  if (visited[v]) {
    return false;
  }
  visited[v] = true;
  for (int u : adj[v]) {
    if (match[u] == -1 || Kuhn(visited, adj, match, match[u])) {
      match[u] = v;
      return true;
    }
  }
  return false;
}

int ReadBoard(std::vector<std::vector<bool>>& covered,
              std::map<std::pair<int, int>, int>& cell_index, int rows,
              int cols) {
  int white = 0;
  int black = 0;
  int free_cells = 0;
  std::string row;
  for (int i = 0; i < rows; ++i) {
    std::cin >> row;
    for (int j = 0; j < cols; ++j) {
      covered[i][j] = row[j] == '.';
      if ((i + j) % 2 != 0) {
        ++black;
        cell_index[{i, j}] = black;
      } else {
        ++white;
        cell_index[{i, j}] = white;
      }
      if (!covered[i][j]) {
        ++free_cells;
      }
    }
  }
  return free_cells;
}

auto BuildGraph(const std::vector<std::vector<bool>>& covered,
                std::map<std::pair<int, int>, int>& cell_index, int rows,
                int cols) {
  int white_count = (rows * cols + 1) / 2;
  std::vector<std::vector<int>> adj(white_count + 1);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (covered[i][j] || (i + j) % 2 != 0) {
        continue;
      }
      if (i != 0 && !covered[i - 1][j]) {
        adj[cell_index[{i, j}]].push_back(cell_index[{i - 1, j}]);
      }
      if (i != rows - 1 && !covered[i + 1][j]) {
        adj[cell_index[{i, j}]].push_back(cell_index[{i + 1, j}]);
      }
      if (j != 0 && !covered[i][j - 1]) {
        adj[cell_index[{i, j}]].push_back(cell_index[{i, j - 1}]);
      }
      if (j != cols - 1 && !covered[i][j + 1]) {
        adj[cell_index[{i, j}]].push_back(cell_index[{i, j + 1}]);
      }
    }
  }
  return adj;
}

int main() {
  int rows;
  int cols;
  int domino_cost;
  int square_cost;
  std::cin >> rows >> cols >> domino_cost >> square_cost;

  int white_count = (rows * cols + 1) / 2;
  int black_count = (rows * cols) / 2;

  std::vector<std::vector<bool>> covered(rows, std::vector<bool>(cols));
  std::map<std::pair<int, int>, int> cell_index;
  int free_cells = ReadBoard(covered, cell_index, rows, cols);
  auto adj = BuildGraph(covered, cell_index, rows, cols);

  std::vector<int> match(black_count + 1, -1);
  for (int v = 1; v <= white_count; ++v) {
    std::vector<bool> visited(white_count + 1, false);
    Kuhn(visited, adj, match, v);
  }

  int total = 0;
  int paired_cells = 0;
  for (int u = 1; u <= black_count; ++u) {
    if (match[u] != -1) {
      total += std::min(domino_cost, 2 * square_cost);
      paired_cells += 2;
    }
  }

  std::cout << total + (free_cells - paired_cells) * square_cost << "\n";
  return 0;
}
