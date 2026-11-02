
/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min
 * accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/

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

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        int n = intervals.size();
        std::sort(intervals.begin(), intervals.end(), [&](auto x, auto y) -> bool {
            return x[0] < y[0];
        });
        std::vector<vector<int>>ans;
        ans.push_back(intervals[0]); int Max = intervals[0][1];
        for(i64 i = 1;i < n ;i ++) {
            if(intervals[i][0] <= Max) {
                Max = std::max(Max, intervals[i][1]); i64 sz = ans.size();
                ans[sz - 1][1] = Max;
            } else {
                ans.push_back(intervals[i]);
                Max = intervals[i][1];
            }
        }
        return ans;
    }
};