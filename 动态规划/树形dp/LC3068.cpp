
/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/

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

class Solution {
public:
  long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
    i64 n = nums.size();
    nums.insert(nums.begin(), 0ll);
    std::vector<std::vector<i64>>g(n + 1);
    for (auto e : edges) {
      g[e[0] + 1].push_back(e[1] + 1);
      g[e[1] + 1].push_back(e[0] + 1);
    }
    std::vector dp(n + 1, std::array<i64, 2> {0, -inf});
    std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
      for (auto v : g[u]) {
        if (v == f)continue;
        dfs(v, u);
        std::array<i64, 2>nxt;
        for (i64 i = 0; i <= 1; i++) {
          nxt[i] = dp[u][i] + std::max(dp[v][0], dp[v][1]);
          nxt[i] = std::max(nxt[i], dp[u][1 - i] + std::max(dp[v][0] + (nums[v] ^ k) - nums[v], dp[v][1] + nums[v] - (nums[v] ^ k)));
        }
        dp[u] = nxt;
      }
      dp[u][0] += nums[u]; dp[u][1] += (nums[u] ^ k);
    };

    /*
  std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
      dp[u][0] = nums[u]; dp[u][1] = -inf;
      bool flag = true;
      for (auto v : g[u]) {
        if (v == f)continue;
        dfs(v, u);
        std::array<i64, 2>nxt;
        if (flag) {
          flag = false;
          nxt[0] = dp[u][0] + std::max(dp[v][0], dp[v][1]);
          nxt[1] = std::max(dp[u][0] + dp[v][0] - nums[u] - nums[v] + (nums[u] ^ k) + (nums[v] ^ k),
                            dp[u][0] + dp[v][1] - nums[u] + (nums[u] ^ k) - (nums[v] ^ k) + nums[v]);
        } else {
          nxt[0] = dp[u][0] + std::max(dp[v][0], dp[v][1]);
          nxt[0] = std::max(nxt[0], std::max(dp[u][1] + dp[v][0] - (nums[u] ^ k) - nums[v] + nums[u] + (nums[v] ^ k),
                                             dp[u][1] + dp[v][1] - (nums[u] ^ k) - (nums[v] ^ k) + nums[u] + nums[v]));
          nxt[1] = dp[u][1] + std::max(dp[v][0], dp[v][1]);
          nxt[1] = std::max(nxt[1], std::max(dp[u][0] + dp[v][0] - (nums[u]) - nums[v] + (nums[u] ^ k) + (nums[v] ^ k),
                                             dp[u][0] + dp[v][1] - (nums[u]) - (nums[v] ^ k) + (nums[u] ^ k) + nums[v]));
        }
        dp[u] = nxt;
      }
      //dp[u][0] += nums[u]; dp[u][1] += (nums[u] ^ k);
    };
    */
    dfs(1, 0);
    return std::max(dp[1][0], dp[1][1]);
  }
};


/*


*/