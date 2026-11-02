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
  
  i64 ans = 0;
  std::vector<i64>sz(n + 1);
  std::function<void(i64)>dfs1 = [&](i64 u) {
    sz[u] = 1;
    for(i64 i = 0;i <= 1;i ++) {
      if(son[u][i] == -1)continue;
      dfs1(son[u][i]);
      sz[u] += sz[son[u][i]];
    }
  };
  dfs1(1);
  std::function<bool(i64, i64)>dfs = [&](i64 x, i64 y) {
    if(x == -1 and y == -1)return true;
    if(x == -1 or y == -1)return false;
    if(v[x] != v[y]) return false;
    return dfs(son[x][0], son[y][1]) and dfs(son[x][1], son[y][0]);
  };
  dfs(1, 0);
  i64 ans = 0;
  for(i64 i = 1;i <= n;i ++)if(dfs(i, i))ans = std::max(ans, sz[i]);
  std::cout << ans << "\n";
}