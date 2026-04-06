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
  i64 n;
  std::cin >> n;
  std::vector<i64>a(n + 1);
  for(i64 i = 1;i <= n;i ++) {
    std::cin >> a[i];
  }
  i64 sum = accumulate(a.begin() + 1,a.begin() + 1 + n, 0ll);
  std::sort(a.begin() + 1, a.begin() + 1 + n, [&](i64 x,i64 y) -> bool {
    return x > y;
  });
  i64 len = 0;
  std::vector<bool>vis(n + 1, false);
  std::function<bool(i64, i64, i64)>dfs = [&](i64 idx, i64 cnt, i64 res) {
    if(cnt == 0)return true;
    if(res == 0)return dfs(1, cnt - 1, len);
    for(i64 i = idx; i <= n;i ++) {
      if(a[i] > res)continue;
      if(vis[i])continue;
      vis[i] = true;
      bool f = dfs(i + 1, cnt, res - a[i]);
      if(f)return true;
      vis[i] = false;
      if(res == a[i] or res == len)break;
      while(i < n and a[i] == a[i + 1])i ++;
    }
    return false;
  };
  for(len = a[1]; len <= sum; len ++) {
    if(sum % len)continue;
    bool f = dfs(1, sum / len, len);
    if(f)break;
  }
  std::cout << len << "\n";
  return 0;
}