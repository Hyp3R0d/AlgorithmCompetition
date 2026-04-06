/*折半搜索*/
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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
int main() {
	std::map<string, i64> d1, d2;
	string s1;
	std::cin >> s1;
	std::string s2 = "123804765";
	d1[s1] = 0;
	d2[s2] = 0;
	queue<string>q;
	q.push(s1);
	std::vector<std::pair<i64, i64>>dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
	auto check = [&](i64 x, i64 y) -> bool {
		return x >= 0  and x <= 2 and y >= 0 and y <= 2;
	};
	if(s1 == s2) {
		puts("0"); exit(0);
	}
	while(q.size()) {
		string p1 = q.front();
		q.pop();
		if(d1[p1] >= 20)continue; // 剪枝
		i64 pos = p1.find('0');
		i64 fx = pos / 3, fy = pos % 3;
		for(auto [dx, dy] : dir) {
			i64 ffx = fx + dx, ffy = fy + dy;
			if(check(ffx, ffy)) {
				auto p2 = p1;
				swap(p2[ffx * 3 + ffy], p2[pos]);
				if(d2.count(p2)) {
					std::cout << d2[p2] + d1[p1] + 1 << "\n";
					return 0;
				}
				if(not d1.count(p2)) {
					d1[p2] = d1[p1] + 1;
					q.push(p2);
				}
			}
		}
	}
	q.push(s2);
	while(q.size()) {
		string p1 = q.front();
		q.pop();
		if(d2[p1] >= 20)continue; // 剪枝
		i64 pos = p1.find('0');
		i64 fx = pos / 3, fy = pos % 3;
		for(auto [dx, dy] : dir) {
			i64 ffx = fx + dx, ffy = fy + dy;
			if(check(ffx, ffy)) {
				auto p2 = p1;
				swap(p2[ffx * 3 + ffy], p2[pos]);
				if(d1.count(p2)) {
					std::cout << d1[p2] + d2[p1] + 1 << "\n";
					return 0;
				}
				if(not d2.count(p2)) {
					d2[p2] = d2[p1] + 1;
					q.push(p2);
				}
			}
		}
	}
	return 0;
 }