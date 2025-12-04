/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/


#include<bits/stdc++.h>

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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;





class Solution {
public:
  long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
    std::sort(robot.begin(), robot.end());
    std::sort(factory.begin(), factory.end(), [&](std::vector<int>x, std::vector<int>y)->bool{
      return x[0] < y[0];
    });
    i64 n = factory.size(), m = robot.size();
    std::vector dp(n + 1, std::vector<i64>(m + 1, inf));
    dp[0][0] = 0;
    for (i64 i = 1; i <= n; i++) {
      for (i64 j = 0; j <= m; j++) {
        i64 total = 0;
        for (i64 k = 0; k <= std::min(j, (i64)factory[i - 1][1]); k++) {

          if (k >= 1)total += abs(robot[j - k + 1 - 1] - factory[i - 1][0]);
          dp[i][j] = std::min(dp[i][j], dp[i - 1][j - k] + total);
        }
      }
    }
    return dp[n][m];
  }
};


class Solution {
public:
  long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
    std::sort(robot.begin(), robot.end());
    std::sort(factory.begin(), factory.end(), [&](std::vector<int>x, std::vector<int>y)->bool{
      return x[0] < y[0];
    });
    i64 n = factory.size(), m = robot.size();
    std::vector dp(m + 1, inf);
    dp[0] = 0;
    for (i64 i = 1; i <= n; i++) {
      for (i64 j = m; j >= 1; j--) {
        i64 total = 0;
        for (i64 k = 1; k <= std::min(j, (i64)factory[i - 1][1]); k++) {
          total += abs(factory[i - 1][0] - robot[j - k]);
          dp[j] = std::min(dp[j], dp[j - k] + total);
        }
      }
    }
    return dp[m];
  }
};


