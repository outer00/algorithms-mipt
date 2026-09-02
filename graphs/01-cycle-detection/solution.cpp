#include <iostream>
#include <set>
#include <vector>

enum struct Color { White, Grey, Black };

struct Node {
  int number = 0;
  Color color = Color::White;
  std::set<Node*> edges;
};

std::vector<int> cycle;
int cycle_start = 0;
bool cycle_closed = false;

bool Dfs(Node& node) {
  node.color = Color::Grey;
  for (Node* next : node.edges) {
    if (next->color == Color::Grey) {
      cycle.push_back(next->number);
      cycle.push_back(node.number);
      cycle_start = next->number;
      return true;
    }
    if (next->color == Color::White && Dfs(*next)) {
      if (node.number == cycle_start) {
        cycle_closed = true;
      }
      if (!cycle_closed) {
        cycle.push_back(node.number);
      }
      return true;
    }
  }
  node.color = Color::Black;
  return false;
}

bool PrintCycle(Node& node) {
  if (!Dfs(node)) {
    return false;
  }
  std::cout << "YES\n";
  for (auto iter = cycle.rbegin(); iter != cycle.rend(); ++iter) {
    std::cout << *iter << ' ';
  }
  return true;
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;

  std::vector<Node> graph(vertices + 1);
  for (int i = 1; i <= vertices; ++i) {
    graph[i].number = i;
  }

  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    graph[from].edges.insert(&graph[to]);
  }

  for (int i = 1; i <= vertices; ++i) {
    if (graph[i].color == Color::White && PrintCycle(graph[i])) {
      break;
    }
    if (i == vertices) {
      std::cout << "NO";
    }
  }
  return 0;
}
