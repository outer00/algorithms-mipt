#include "iostream"
#include "set"
#include "vector"

enum struct Color { White, Grey, Black };

struct Node {
  int number = 0;
  Color color = Color::White;
  std::set<Node*> edges;
};

std::vector<int> ans;
int begin = 0;
bool flag = false;

bool DFS(Node& node) {
  node.color = Color::Grey;
  for (auto* income : node.edges) {
    if (income->color == Color::Grey) {
      ans.push_back((*income).number);
      ans.push_back(node.number);
      begin = (*income).number;
      return true;
    }
    if (income->color == Color::White && DFS(*income)) {
      if (node.number == begin) {
        flag = true;
      }
      if (!flag) {
        ans.push_back(node.number);
      }
      return true;
    }
  }
  node.color = Color::Black;
  return false;
}

bool Check(Node& node) {
  if (DFS(node)) {
    std::cout << "YES\n";
    for (auto iter = ans.end(); iter != ans.begin(); --iter) {
      std::cout << *(iter - 1) << ' ';
    }
    return true;
  }
  return false;
}

int main() {
  int num;
  int mnum;
  std::cin >> num >> mnum;
  std::vector<Node> graph(num + 1);
  for (int i = 1; i < num + 1; ++i) {
    graph[i].number = i;
  }
  int outcome;
  int income;
  for (int i = 0; i < mnum; ++i) {
    std::cin >> outcome >> income;
    graph[outcome].edges.insert(&graph[income]);
  }
  for (int i = 1; i < num + 1; ++i) {
    if (graph[i].color == Color::White && Check(graph[i])) {
      break;
    }
    if (i == num) {
      std::cout << "NO";
    }
  }
  return 0;
}