#include <iostream>
#include <map>
#include <string>

void OptimizeIO() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  OptimizeIO();

  int users;
  std::cin >> users;

  std::map<std::string, std::string> pair_of;
  for (int i = 0; i < users; ++i) {
    std::string login;
    std::string password;
    std::cin >> login >> password;
    pair_of[login] = password;
    pair_of[password] = login;
  }

  int queries;
  std::cin >> queries;
  for (int i = 0; i < queries; ++i) {
    std::string word;
    std::cin >> word;
    std::cout << pair_of[word] << '\n';
  }
  return 0;
}
