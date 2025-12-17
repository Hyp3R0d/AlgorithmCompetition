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


// 贡献法
class Solution {
public:
	long long appealSum(string s) {
		i64 n = s.size();
		// 对于子串中的每个字符，只考虑其第一次出现时候的贡献
		s = " " + s; i64 ans = 0;
		std::vector<i64>pre(30, 0);
		for (i64 i = 1; i <= n; i++) {
			ans += (i - pre[i]) * (n - i + 1);
		}
		return ans;
	}
};



// 增量法
class Solution {
public:
	long long appealSum(string s) {
		i64 n = s.size();
		s = " " + s; i64 ans = 0;
		std::vector<i64>pre(30, 0);
		i64 sum = 0;
		for (i64 i = 1; i <= n; i++) {
			sum += (i - pre[s[i] - 'a']);
			ans += sum;
			pre[s[i] - 'a'] = i;
		}
		return ans;
	}
};


