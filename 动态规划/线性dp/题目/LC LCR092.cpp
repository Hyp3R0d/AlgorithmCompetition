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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;



class Solution {
public:
	int minFlipsMonoIncr(string s) {
		i64 n = s.size();
		s = " " + s;
		std::vector dp(n + 1, std::vector<i64>(2, inf));
		if (s[1] == '0')dp[1][0] = 0, dp[1][1] = 1;
		else dp[1][0] = 1, dp[1][1] = 0;

		for (i64 i = 2; i <= n; i++) {
			if (s[i] == '0')dp[i][0] = std::min(dp[i][0], dp[i - 1][0]),
				                           dp[i][1] = std::min(dp[i][1], std::min(dp[i - 1][1], dp[i - 1][0])  + 1);
			else {
				dp[i][0] = std::min(dp[i][0], dp[i - 1][0] + 1);
				dp[i][1] = std::min(dp[i][1], std::min(dp[i - 1][0], dp[i - 1][1]));
			}
		}
		return std::min(dp[n][1], dp[n][0]);
	}
};