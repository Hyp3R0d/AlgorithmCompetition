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
	std::vector<i64> Manacher(string s) {
		i64 len = s.size();
		std::string st(len * 2 + 5, ' ');
		for (i64 i = 0; i < len; i++) {
			st[i * 2] = '#'; st[i * 2 + 1] = s[i];
		}
		st[len * 2] = '#';
		std::vector<i64>d(2 * len + 5);
		for (i64 i = 0, l = 0, r = -1; i < len * 2 + 1; i++) {
			i64 k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
			while (i - k >= 0 and i + k < 2 * len + 1 and st[i - k] == st[i + k])k++;
			d[i] = k--;
			if (i + k > r) {
				l = i - k; r = i + k;
			}
		}//维护的是st串的最长回文半径
		return d;
	}
	long long maxProduct(string s) {
		auto d = Manacher(s);
		i64 len = s.size();
		std::vector<i64>pre(len), suf(len);
		for (i64 i = 1; i <= 2 * len - 1; i++) {
			if (i & 1) {
				i64 idx = i / 2, length = d[i] / 2;
				pre[idx + length - 1] = max(pre[idx + length - 1], 2 * length - 1);
				suf[idx - length + 1] = max(2 * length - 1, suf[idx - length + 1]);
			}
		}
        
		for (i64 i = len - 2; i >= 0; i--) {
			pre[i] = std::max(pre[i], pre[i + 1] - 2);
		}
        for(i64 i = 1;i <= len - 1;i ++) pre[i] = std::max(pre[i] ,pre[i - 1]);
		for (i64 i = 1; i <= len - 1; i ++) {
			suf[i] = std::max(suf[i], suf[i - 1] - 2);
		}
        for (i64 i = len - 2; i >= 0; i--) {
			suf[i] = std::max(suf[i], suf[i + 1] - 2);
		}
		i64 ans = 0;
		for (i64 i = 0; i <= len - 2; i++) {
			ans = std::max(ans, pre[i] * suf[i + 1]);
		}
		return ans;
	}
};