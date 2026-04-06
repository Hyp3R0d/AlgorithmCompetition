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
	int deleteString(string s) {
		i64 n = s.size(); s = " " + s;
		vector<i64>dp(n + 5, 0);
		dp[0] = 0;
		const i64 b = 23;
		auto qpow = [&](i64 a, i64 b) {
			int ret = 1;
			while (b) {
				if (b & 1)ret = ret * a % mod;
				a = a * a % mod;
				b >>= 1;
			}
			return ret;
		};
		vector<i64>Hash(n + 5, 0);
		for (i64 i = 1; i <= n; i++) {
			Hash[i] = (Hash[i - 1] % mod * b % mod + s[i] - 'a') % mod;
		}
		auto get = [&](i64 l, i64 r)  {
			return ((Hash[r] - Hash[l - 1] % mod * qpow(b, r - l + 1) % mod) % mod + mod) % mod;
		};
		for (int i = n; i >= 1; i--) {
			for (int len = 2; i + len - 1 <= n; len += 2) {
				int j = i + len - 1;
				if (get(i, i + len / 2 - 1) == get(i + len / 2, j)) {
					dp[i] = max(dp[i], dp[i + len / 2] + 1);
				}
            }
            dp[i] = std::max(dp[i], dp[n + 1] + 1);
		}
		return dp[1];
	}
};


/*自然溢出哈希*/


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
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
  int deleteString(string s) {
    i64 n = s.size();
    s = " " + s;
    std::vector<u64> stringHash(n + 1);
    u64 base = 233;
    for (i64 i = 1; i <= n; i++) {
      stringHash[i] = (stringHash[i - 1] * base + s[i] - 'a');
    }
    auto qpow = [&](u64 u, i64 v) -> u64 {
      u64 ret = 1;
      while (v) {
        if (v & 1)
          ret = ret * u;
        u = u * u;
        v >>= 1;
      }
      return ret;
    };
    auto getHash = [&](i64 l, i64 r) {
      return stringHash[r] - stringHash[l - 1] * qpow(base, r - l + 1);
    };
    std::vector<i64> dp(n + 5);
    for (i64 i = n; i >= 1; i--)  {
      for(i64 len = 2; len <= n - i + 1;len += 2) {
        if(getHash(i, i + len / 2 - 1) == getHash(i + len / 2, i + len - 1)) {
          dp[i] = std::max(dp[i], dp[i + len / 2] + 1);
        }
      }
      dp[i] = std::max(dp[i], 1ll);
    }
    return dp[1];
  }
};