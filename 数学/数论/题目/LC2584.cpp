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
  i64 son[1000005];
  int findValidSplit(vector<int>& nums) {
    memset(son, 0, sizeof(son));

    for (i64 i = 2; i <= 1e6; i++) {
      if (not son[i]) {
        son[i] = i;
        for (i64 j = i + i; j <= 1e6; j += i) {
          if (not son[j])son[j] = i;
        }
      }
    }
    i64 n = nums.size();
    std::unordered_map<i64, i64>w;
    std::vector<vector<pair<i64, i64>>>z(n);
    for (i64 i = 0; i < n; i++) {
      i64 v = nums[i];

      while (v != 1) {
        i64 las = son[v]; i64 cnt = 0;
        while (v % las == 0) {
          v /= las; cnt++;
        }
        z[i].push_back({las, cnt});
        w[las] += cnt;
      }
    }

    std::unordered_map<i64, i64>g; i64 tot = 0;
    for (i64 i = 0; i <= n - 2; i++) {
      for (auto [v, cnt] : z[i]) {
        g[v] += cnt;
        if (g[v] == w[v])tot++;
      }
      if (tot == g.size())return i;
    }
    return -1;
  }
};