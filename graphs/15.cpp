#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

void GetAns(const std::list<long long>& ans) {
  std::cout << ans.size() << "\n";
  for (auto v : ans) {
    std::cout << v << " ";
  }
}

int main() {
  const long long cInf = 1e17;
  long long n;
  long long m;
  long long k;
  std::cin >> n >> m >> k;
  std::vector<std::vector<std::pair<long long, long long>>> par(
      n, std::vector<std::pair<long long, long long>>(n, {-1, -1}));
  std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, cInf));
  for (long long i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  std::vector<std::vector<std::pair<long long, long long>>> g(
      n, std::vector<std::pair<long long, long long>>(n));
  std::vector<long long> selected(k);
  for (long long i = 0; i < m; ++i) {
    long long w;
    long long u;
    long long v;
    std::cin >> u >> v >> w;
    --u;
    --v;
    if (-w < dist[u][v]) {
      dist[u][v] = -w;
      par[u][v] = {u, i + 1};
      g[u][v] = {-w, i + 1};
    }
  }
  for (long long i = 0; i < k; ++i) {
    std::cin >> selected[i];
    --selected[i];
  }
  for (long long p = 0; p < n; ++p) {
    for (long long i = 0; i < n; ++i) {
      if (dist[i][p] == cInf) {
        continue;
      }
      for (long long j = 0; j < n; ++j) {
        if (dist[p][j] == cInf) {
          continue;
        }
        if (dist[i][p] + dist[p][j] < dist[i][j]) {
          par[i][j] = par[p][j];
          dist[i][j] = dist[i][p] + dist[p][j];
        }
      }
    }
  }
  for (long long x = 0; x < n; ++x) {
    if (dist[x][x] < 0) {
      for (long long i = 0; i < n; ++i) {
        if (dist[i][x] == cInf) {
          continue;
        }
        for (long long j = 0; j < n; ++j) {
          if (dist[x][j] == cInf) {
            continue;
          }
          dist[i][j] = -cInf;
        }
      }
    }
  }
  for (long long i = 0; i < k - 1; ++i) {
    long long v = selected[i + 1];
    long long u = selected[i];
    for (long long x = 0; x < n; ++x) {
      if (dist[u][v] == -cInf) {
        std::cout << "infinitely kind\n";
        return 0;
      }
    }
  }
  std::list<long long> ans;
  for (long long i = 0; i < k - 1; ++i) {
    long long v = selected[i + 1];
    long long u = selected[i];

    std::list<long long> path;
    long long cur = v;
    while (cur != u) {
      long long next_cur;
      long long id;
      std::tie(next_cur, id) = par[u][cur];
      cur = next_cur;
      path.push_back(id);
    }
    path.reverse();
    ans.insert(ans.end(), path.begin(), path.end());
  }
  GetAns(ans);
  return 0;
}
