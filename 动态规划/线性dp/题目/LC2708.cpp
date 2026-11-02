

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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    long long maxStrength(vector<int>& nums) {
        i64 n = nums.size();
        std::vector<i64>p(2, 0);   
        for(i64 i = 0;i < n;i ++) {
          if(nums[i] > 0) {
            p[0] = std::max({p[0], (i64)nums[i], p[0] * (i64)nums[i]});
            p[1] = std::min(p[1], p[1] * (i64)nums[i]);
          } else if(nums[i] < 0) {
            i64 pre = p[1];
            p[1] = std::min({p[1], (i64)nums[i], p[0] * (i64)nums[i]});
            p[0] = std::max(p[0], pre * (i64)nums[i]);
          }
        }
        return p[0];
    } 
};