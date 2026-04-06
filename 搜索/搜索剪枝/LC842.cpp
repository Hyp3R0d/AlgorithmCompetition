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
    vector<int> splitIntoFibonacci(string num) {
        int len = num.size(); vector<int>p;
        function<bool(int)>dfs = [&](int idx) {
            if (idx >= len) {
                //for (auto c : p)std::cout  << c << "\n";
;
                return p.size() >= 3;
            }
            i64 cur = 0;
            for (int i = idx; i < len; i++) {
                if (i > idx and num[idx] == '0')break;
                cur = cur * 10 + num[i] - '0';
                if (cur >= (1ll << 31))break;
                if (p.size() >= 2) {
                    i64 pre = (i64)p[p.size() - 1] + (i64)p[p.size() - 2];
                    if (cur < pre)continue;
                    else if (cur > pre)break;
                }
                p.push_back(cur);
                bool f = dfs(i + 1); if (f)return true;
                p.pop_back();
            }
            return false;
        };
        dfs(0); return p;
    }
};


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
  vector<int> splitIntoFibonacci(string num) {
    i64 n = num.size();
    std::vector<int> p;
    std::function<bool(i64)> dfs = [&](i64 idx) -> bool {
      if (idx == n) {
        if (p.size() >= 3)
          return true;
        else
          return false;
      }
      if (p.size() >= 2) {
        i64 cur = 0;
        i64 pre = p[p.size() - 1] + p[p.size() - 2];
        for (i64 i = idx; i < n; i++) {
          if (num[idx] == '0' and i > idx)
            break;
          cur = cur * 10 + num[i] - '0';
          if (cur < pre)
            continue;
          if (cur == pre) {
            p.push_back(cur);
            bool f = dfs(i + 1);
            if (f)
              return true;
            p.pop_back();
            return false;
          }
          if (cur > pre)
            return false;
        }
        return false;
      } else {
        i64 cur = 0;
        for (i64 i = idx; i < n; i++) {
          if (num[idx] == '0' and i > idx)
            break;
          cur = cur * 10 + num[i] - '0';
          if(cur > (1ll << 32) - 1)break;
          p.push_back(cur);
          bool f = dfs(i + 1);
          if (f)
            return true;
          p.pop_back();
        }
        return false;
      }
    };
    dfs(0);
    return p;
  }
};