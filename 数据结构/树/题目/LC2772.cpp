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
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
  bool checkArray(vector<int>& nums, int k) {
    i64 n = nums.size();
    std::vector<i64>a(n + 1);
    for (i64 i = 1; i <= n; i++)a[i] = nums[i - 1];
    std::vector<i64>tr(n + 1);
    auto add = [&](i64 idx, i64 v) {
      for (; idx <= n; idx += (idx & -idx))tr[idx] += v;
    };
    auto query = [&](i64 idx) {
      i64 ret = 0;
      for (; idx >= 1; idx -= (idx & -idx))ret += tr[idx];
      return ret;
    };
    for (i64 i = 1; i <= n; i++) {
      add(i, a[i] - a[i - 1]);
    }
    for (i64 i = 1; i <= n; i++) {
      if (query(i) < 0)return false;
      if (query(i) == 0)continue;
      i64 d = query(i);
      i64 r = i + k - 1; if (r > n)return false;
      add(i, -d); add(r + 1, d);
    }
    return true;
  }
};
