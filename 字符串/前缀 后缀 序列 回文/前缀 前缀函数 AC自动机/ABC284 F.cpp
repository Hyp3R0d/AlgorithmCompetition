
/*KMP*/
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


std::vector<i64> PrefixFunction(string s) {
	i64 len = s.size();
	std::vector<i64>p(len + 5, 0);
	for (i64 i = 1; i < len; i++) {
		i64 j = p[i - 1];
		while (j > 0 and s[i] != s[j])j = p[j - 1];
		if (s[i] == s[j])j++;
		p[i] = j;
	}//KMP函数板题
	return p;
}

int main() {
	i64 n; string t; std::cin >> n >> t;
	string tmp = t; reverse(tmp.begin(), tmp.end());
	string tmp1 = t + tmp;
	auto prefix1 = PrefixFunction(tmp1);
	string tmp2 = tmp + t;
	auto prefix2 = PrefixFunction(tmp2);
	string ans = "";
	for (int i = 0; i <= n; i++) {
		if (prefix1[3 * n - 1] >= i and prefix2[3 * n - 1] >= n - i) {
			for (int j = 0; j < i; j++)ans.push_back(t[j]);
			for (int j = n + i; j < n * 2; j++)ans.push_back(t[j]);
			std::cout << ans << "\n";
			std::cout << i << "\n";
			return 0;
		}
	}
	puts("-1");
	return 0;
}



/*字符串单哈希*/

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

const u64 base = 13331;

struct PolyHash {
	std::vector<u64>h, p;
	PolyHash(string s): h(s.size() + 1), p(s.size() + 1, 1) {

		i64 n = s.size();
		s = " " + s;
		for (i64 i = 1; i <= n; i++) {
			h[i] = h[i - 1] * base + s[i];
			p[i] = p[i - 1] * base;
		}
	}
	u64 get(i64 l, i64 r) {
		return h[r] - h[l - 1] * p[r - l + 1];
	}
};


int main() {
	i64 n; std::cin >> n;
	string t; std::cin >> t;
	string t2 = t;
	std::reverse(t2.begin(), t2.end());
	PolyHash h1(t);
	PolyHash h2(t2);
	for (i64 i = 0; i <= n; i++) {
		bool f1 = (h1.get(1, i) == h2.get(n - i + 1, n));
		bool f2 = (h1.get(i + 1, n) == h2.get(1, n - i));
		if (f1 and f2) {
			string ans = t.substr(i, n);
			reverse(ans.begin(), ans.end());
			std::cout << ans << "\n" << i;
			return 0;
		}
	}
	puts("-1"); return 0;
}


/*字符串双哈希*/


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


const i64 MOD1 = 1e9 + 7;
const i64 MOD2 = 1e9 + 9;

// 使用随机数生成器生成 Base，防止针对固定 Base 的 Hack 数据
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const i64 BASE1 = std::uniform_int_distribution<i64>(131, MOD1 - 1)(rng);
const i64 BASE2 = std::uniform_int_distribution<i64>(131, MOD2 - 1)(rng);

struct DoubleHash {
	vector<i64> h1, p1;
	vector<i64> h2, p2;

	DoubleHash(const string& s) {
		int n = s.size();
		h1.resize(n + 1, 0); p1.resize(n + 1, 1);
		h2.resize(n + 1, 0); p2.resize(n + 1, 1);

		for (int i = 0; i < n; i++) {
			// Hash 1
			h1[i + 1] = (h1[i] * BASE1 + s[i]) % MOD1;
			p1[i + 1] = (p1[i] * BASE1) % MOD1;
			// Hash 2
			h2[i + 1] = (h2[i] * BASE2 + s[i]) % MOD2;
			p2[i + 1] = (p2[i] * BASE2) % MOD2;
		}
	}

	// 获取子串 [l, r) 的双哈希值
	// 返回 pair，只有当两个哈希值都相等时，才视为子串相等
	pair<i64, i64> get(int l, int r) {
		i64 res1 = (h1[r] - h1[l - 1] * p1[r - l + 1]) % MOD1;
		if (res1 < 0) res1 += MOD1;

		i64 res2 = (h2[r] - h2[l - 1] * p2[r - l + 1]) % MOD2;
		if (res2 < 0) res2 += MOD2;

		return {res1, res2};
	}
};


int main() {
	// 优化 I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	if (!(cin >> N)) return 0;

	string T;
	cin >> T;

	// 将 T 分割为左右两半 L 和 R
	string L = T.substr(0, N);
	string R = T.substr(N, N);

	// 创建反转版本
	string L_rev = L;
	reverse(L_rev.begin(), L_rev.end());

	string R_rev = R;
	reverse(R_rev.begin(), R_rev.end());

	// 构建双重哈希对象
	DoubleHash hash_L(L);
	DoubleHash hash_R(R);
	DoubleHash hash_L_rev(L_rev);
	DoubleHash hash_R_rev(R_rev);

	// 枚举所有可能的分割点 i
	for (int i = 0; i <= N; ++i) {
		// 条件 1: L 的前缀 (len i) == R 的前缀的反转 (即 R_rev 的后缀)
		// L[0...i] vs R_rev[N-i...N]
		bool cond1 = (hash_L.get(0, i) == hash_R_rev.get(N - i, N));

		// 条件 2: R 的后缀 (len N-i) == L 的后缀的反转 (即 L_rev 的前缀)
		// R[i...N] vs L_rev[0...N-i]
		bool cond2 = (hash_R.get(i, N) == hash_L_rev.get(0, N - i));

		if (cond1 and cond2) {
			// 找到解
			// T 的中间部分 T[i ... i+N-1] 是 S 的反转
			// 我们提取这一段并再次反转回来得到 S
			string S_reverse = T.substr(i, N);
			string S = S_reverse;
			reverse(S.begin(), S.end());

			cout << S << "\n" << i;
			return 0;
		}
	}

	// 无解
	puts("-1");

	return 0;
}