#include<bits/extc++.h>

using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
using u32 = unsigned int;
using f32 = float;
using i64 = signed long long;
using u64 = unsigned long long;
using f64 = double;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using namespace std;

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


struct cmp {
  bool operator()(const array<i64, 3>&x, const array<i64, 3>&y) const {
    return x[0] > y[0];
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  i64 k, n, m; std::cin >> k >> n >> m;
  vector<vector<array<i64, 3>>>g(n + 1);
  for (i64 i = 1; i <= m; i++) {
    i64 u, v, t, h; std::cin >> u >> v >> t >> h;
    g[u].push_back({v, t, h});
    g[v].push_back({u, t, h});
  }
  vector dis(n + 1, vector<i64>(k + 5, inf));
  i64 s, t; std::cin >> s >> t;
  dis[s][0] = 0;
  priority_queue<array<i64, 3>, vector<array<i64, 3>>, cmp>q;
  q.push({0, s, 0});
  //vector<bool>vis(n + 1, false);
  std::vector vis(n + 1, std::vector<bool>(k + 1, false));
  while (q.size()) {
    auto [d, u, h] = q.top(); q.pop();
    if (u == t) {
      std::cout << d << "\n";
      return 0;
    }
    if (vis[u][h])continue;
    vis[u][h] = true;
    for (auto [v, t, h] : g[u]) {
      for (i64 j = 0; j < k; j++) {
        if (j >= h) {
          if (dis[u][j - h] + t < dis[v][j]) {
            dis[v][j] = min(dis[v][j], dis[u][j - h] + t);
            if (not vis[v][j]) {
              q.push({dis[v][j], v, j});
            }
          }
        }
      }
    }
  }
  i64 ans = inf;
  for (i64 j = 0; j < k; j++) {
    ans = min(ans, dis[t][j]);
  }
  if (ans == inf) {
    puts("-1"); return 0;
  }
  std::cout  << ans << "\n";
}