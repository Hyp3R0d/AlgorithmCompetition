#include <bits/extc++.h>

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

int main() {
  /*dp*/
  i64 n;std::cin >> n;
  std::vector<i64>a(n + 1);
  for(i64 i = 1;i <= n; i ++) {
    std::cin >> a[i];
  }
  /*
  i64 dp1 = a[1], dp2 = a[1];
  for(i64 i = 2;i <= n; i ++)  {
    dp1 = std::max(a[i], dp1 + a[i]);
    dp2 = std::max(dp1 ,dp2);
  }
  std::cout << dp2 << "\n";
  */
  /*分治*/
  auto cross = [&](i64 l, i64 mid, i64 r)  {
    i64 cur = 0;
    i64 l1 = -inf, l2 = -inf;
    for(i64 i = mid; i >= l; i--) {
      cur += a[i];
      l1 = std::max(l1, cur);
    }
    cur = 0;
    for(i64 i = mid + 1;i <= r; i ++) {
      cur += a[i]; l2 = std::max(l2, cur);
    }
    return l1 + l2;
  };  
  std::function<i64(i64,i64)>dfs = [&](i64 l, i64 r) {
    if(l == r) return a[l];
    i64 mid = (l + r) >> 1;
    i64 lmax = dfs(l, mid); i64 rmax = dfs(mid + 1, r);
    i64 mmax = cross(l, mid, r);
    return std::max({lmax, rmax, mmax});
  };

  
  std::cout << dfs(1, n);
}
