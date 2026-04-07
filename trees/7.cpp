#include <iostream>
#include <map>

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();
  int n;
  std::cin >> n;
  std::map<std::string, std::string> m;
  for (int i = 0; i < n; ++i) {
    std::string a;
    std::string b;
    std::cin >> a >> b;
    m[a] = b;
    m[b] = a;
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string a;
    std::cin >> a;
    std::cout << m[a] << '\n';
  }
}