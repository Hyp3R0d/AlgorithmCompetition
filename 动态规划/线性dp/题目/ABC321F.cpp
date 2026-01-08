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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 Q, K; std::cin >> Q >> K;
	std::vector<i64>dp(K + 1, 0);
	dp[0] = 1;
	while (Q--) {
		string opt; i64 x;
		std::cin >> opt >> x;
		if (opt == "+") {
			for (i64 i = K; i >= x; i--)dp[i] = (dp[i] % mod + dp[i - x]) % mod;
			std::cout << dp[K] << "\n";
		} else {
			for (i64 j = x; j <= K; j++)dp[j] = (dp[j] % mod - dp[j - x] % mod + mod) % mod;
			std::cout << dp[K] << "\n";
		}
	}
	return 0;
}