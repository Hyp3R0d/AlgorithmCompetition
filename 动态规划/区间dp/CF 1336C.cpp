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

void solve() {
	string s, t; std::cin >> s >> t;
	i64 n = s.size(), m = t.size(); s = " " + s; t = " " + t;
	std::vector dp(n + 1, std::vector<i64>(n + 1, 0));
	for (i64 i = 1; i <= n; i++) {
		if (i > m or s[1] == t[i])dp[i][i] = 2;
	}

	for (i64 len = 2; len <= n; len++) {
		for (i64 l = 1; l + len - 1 <= n; l++) {
			i64 r = l + len - 1;
			if (t[l] == s[len] or l > m)dp[l][r] = (dp[l][r] % mod + dp[l + 1][r]) % mod;
			if (t[r] == s[len] or r > m)dp[l][r] = (dp[l][r] % mod + dp[l][r - 1]) % mod;
		}
	}
	i64 ans = accumulate(dp[1].begin() + m, dp[1].begin() + n + 1, 0ll);
	std::cout << ans << "\n";
}
int main() {
	solve();
}