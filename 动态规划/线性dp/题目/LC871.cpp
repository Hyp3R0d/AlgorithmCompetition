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

class Solution {
public:
  int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
    i64 n = stations.size();
    stations.insert(stations.begin(), {0, startFuel});
    std::vector dp(n + 1, std::vector<i64>(n + 1, 0));
    dp[0][0] = startFuel;i64 ans = inf;
    if(startFuel >= target) return 0;
    for (i64 i = 1; i <= n; i++) {
      for(i64 j = 0;j <= n;j ++) {
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
        if(j >= 1 and dp[i - 1][j - 1] >= stations[i][0]) {
          dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + stations[i][1]);
        }
        if(dp[i][j] >= target) ans = std::min(ans, j);
      }
    }
    if(ans == inf) return -1;
    return ans;
  }
};