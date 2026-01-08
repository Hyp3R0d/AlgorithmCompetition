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

i64 a, b;
vector dp(105, vector<i64>(10, 0));
void init() {
	for (i64 i = 0; i <= 9; i++) {
		dp[1][i] = 1;
	}
	for (i64 i = 2; i <= 15; i++) {
		for (i64 j = 0; j <= 9; j++) {
			for (i64 k = j; k <= 9; k++) {
				dp[i][j] += dp[i - 1][k];
			}
		}
	}
}
void solve() {
	//std::cin >> a >> b;

	//00..0 到 99..9 中 以 0 - 9结尾的递增序列

	auto cal = [&](i64 x) {
		vector<i64>num;
		while (x) {
			num.push_back(x % 10); x /= 10;
		}
		i64 res = 0; i64 pre = 0; i64 len = num.size() - 1;
		/*统计位数等于原数的答案数*/
		for (i64 i = len; i >= 0; i--) {
			i64 cur = num[i];
			for (i64 j = (i == len); j < cur; j++) {
				if (j >= pre)res += dp[i + 1][j];
			}
			if (cur < pre)break;
			pre = cur;
			if (not i)res++;
		}
		/*统计位数小于原数的答案数*/
		for (i64 i = 1; i <= len; i++) {
			for (i64 j = 1; j <= 9; j++) {
				res += dp[i][j];
			}
		}
		return res;
	};
	i64 ans =  cal(b) - cal(a - 1);
	std::cout  << ans << "\n";
	;

}
int main() {
	init();
	while (std::cin >> a >> b)
		solve();
}



/* 数位dp 通用模板*/

/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/


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


void solve(i64 a, i64 b) {
	a--;
	string s1 = to_string(a), s2 = to_string(b);
	i64 len1 = s1.size(), len2 = s2.size();
	std::vector dp(len2 + 1, std::vector<i64>(15, -1));
	std::function<i64(const string&, i64, i64, i64, bool, bool)>dfs = [&](const string & s, i64 len, i64 idx, i64 pre, bool isnum, bool islimit)->i64 {
		if (idx == len) return (i64)isnum;
		if (not islimit and isnum and dp[idx][pre]!=-1)return dp[idx][pre];
		i64 res = 0;
		if (not isnum)res += dfs(s, len, idx + 1, pre, false, false);
		i64 low = isnum ? pre : 1;
		i64 up = islimit ? s[idx] - '0' : 9;
		for (i64 d = low; d <= up; d++) {
			i64 ret = dfs(s, len, idx + 1, d, true, islimit and d == up);
			res += ret;
		}
		if (not islimit and isnum)
			dp[idx][pre] = res;
		return res;
	};
	i64 res1 = dfs(s2, len2, 0, 0, false, true);
	dp = std::vector(len2, std::vector<i64>(15, -1));
	i64 res2 = dfs(s1, len1, 0, 0, false, true);
	std::cout << res1 -res2 << "\n";
}

int main() {
	i64 a, b;
	while (std::cin >> a >> b) {
		solve(a, b);
	}
}