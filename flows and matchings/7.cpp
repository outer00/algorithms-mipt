#include "algorithm"
#include "climits"
#include "iostream"
#include "vector"

int from;
int to;
long long capacity;

struct Graph {
  std::vector<int> from;
  std::vector<int> to;
  std::vector<long long> cost;
  std::vector<long long> capacity;
  std::vector<long long> flow;
  std::vector<long long> dst;
  std::vector<int> prev;

  explicit Graph(int n, int m)
      : from(n),
        to(n),
        cost(n),
        capacity(n),
        flow(n),
        dst(m + 1, LLONG_MAX),
        prev(m + 1, -1) {}
};

void Fill(Graph& graph, int m) {
  long long cost;
  for (int i = 0; i < m; ++i) {
    std::cin >> from >> to >> capacity >> cost;
    std::tie(graph.from[2 * i], graph.to[2 * i], graph.cost[2 * i],
             graph.capacity[2 * i], graph.flow[2 * i]) =
        std::make_tuple(from, to, cost, capacity, 0);
    std::tie(graph.from[2 * i + 1], graph.to[2 * i + 1], graph.cost[2 * i + 1],
             graph.capacity[2 * i + 1], graph.flow[2 * i + 1]) =
        std::make_tuple(to, from, -cost, 0, 0);
  }
}

void GetAns(Graph& graph, int n, int m) {
  long long flow;
  long long cost;
  long long ans = cost = 0;
  while (true) {
    int st = 1;
    int end = n;
    graph.dst[st] = 0;
    for (int k = 0; k < n - 1; ++k) {
      for (int i = 0; i < 2 * m; ++i) {
        std::tie(from, to, cost, capacity, flow) =
            std::make_tuple(graph.from[i], graph.to[i], graph.cost[i],
                            graph.capacity[i], graph.flow[i]);
        if (graph.dst[from] != LLONG_MAX && flow < capacity &&
            graph.dst[from] + cost < graph.dst[to]) {
          graph.dst[to] = graph.dst[from] + cost;
          graph.prev[to] = i;
        }
      }
    }
    if (graph.dst[end] != LLONG_MAX) {
      int current = graph.prev[end];
      long long max_flow = LLONG_MAX;
      while (current != -1) {
        max_flow =
            std::min(graph.capacity[current] - graph.flow[current], max_flow);
        current = graph.prev[graph.from[current]];
      }
      current = graph.prev[end];
      cost = 0;
      while (current != -1) {
        graph.flow[current] += max_flow;
        graph.flow[current ^ 1] -= max_flow;
        cost += max_flow * graph.cost[current];
        current = graph.prev[graph.from[current]];
      }
      ans += cost;
    } else {
      std::cout << ans;
      break;
    }
    graph.dst.assign(n + 1, LLONG_MAX);
    graph.prev.assign(n + 1, -1);
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  Graph graph(2 * m, n);
  Fill(graph, m);
  GetAns(graph, n, m);
}