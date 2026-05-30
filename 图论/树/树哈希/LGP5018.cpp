#include <bits/stdc++.h>
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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
  i64 n; std::cin >> n;
  std::vector<u64>v(n + 1);
  for(i64 i = 1; i <= n; i ++) {
    std::cin >> v[i];
  }
  std::vector son(n + 1, vector<i64>(2));
  for(i64 i = 1;i <= n;i ++) {
    cin >> son[i][0] >> son[i][1];
  } 
  std::vector Hash(n + 1, std::vector<u64>(2, 0ll));
  u64 base = 23333;
  std::vector<u64>pw(n + 1);
  pw[0] = 1;
  for(i64 i = 1;i <= n; i ++) {
    pw[i] = pw[i - 1] * base;
  }
  i64 ans = 0;
  std::vector<i64>sz(n + 1);
  std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
    Hash[u][0] = Hash[u][1] = v[u];
    sz[u] = 1;
    for(i64 i = 0; i <= 1;i ++) {
      if(son[u][i] != -1) {
        dfs(son[u][i], u);
        sz[u] += sz[son[u][i]];
      }
    }
    if(son[u][0] != -1)Hash[u][0] = Hash[son[u][0]][0] * base + v[u];
    if(son[u][1] != -1) {
      Hash[u][0] = Hash[u][0] * pw[sz[son[u][1]]] + Hash[son[u][1]][0];
      Hash[u][1] = Hash[son[u][1]][1] * base + v[u];
    }
    if(son[u][0] != -1)Hash[u][1] = Hash[u][1] * pw[sz[son[u][0]]] + Hash[son[u][0]][1];

    if((son[u][0] == -1 and son[u][1] == -1) or (son[u][0] != -1 and son[u][1] != -1 
      and Hash[son[u][0]][0] == Hash[son[u][1]][1]))
      ans = std::max(ans, sz[u]);
  };
  dfs(1, 0);
  std::cout << ans << "\n";
}