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

struct cmp {
	bool operator()(const pair<i64, i64>&x, const pair<i64, i64>&y)const {
		return x.first > y.first;
	}
};

void solve() {
	i64 n, p, x, q, y; std::cin >> n >> p >> x >> q >> y;
	i64 tot = 0;
	std::vector<i64>vis(n);
	std::vector<i64>dis(n, inf);
	priority_queue<std::pair<i64, i64>, std::vector<pair<i64, i64>>, cmp>pq;
	for (i64 i = 1; i <= n; i++) {
		i64 v; std::cin >> v; tot = (tot % n + v) % n;
	}
	dis[tot] = 0;
	pq.push({0, tot});
	while (pq.size()) {
		auto [d, u] = pq.top(); pq.pop();
		if (u == 0) {
			std::cout << d << "\n"; return;
		}
		if (vis[u])continue; vis[u] = true;
		i64 v1 = (u + x) % n;
		if (dis[v1] > dis[u] + p) {
			dis[v1] = dis[u] + p;
			if (not vis[v1]) {
				pq.push({dis[v1], v1});
			}
		}
		i64 v2 = ((u - y) % n + n) % n;
		if (dis[v2] > dis[u] + q) {
			dis[v2] = dis[u] + q;
			if (not vis[v2]) {
				pq.push({dis[v2], v2});
			}
		}
	}
	if (dis[0] == inf) {
		puts("-1"); return;
	}
	std::cout << dis[0] << "\n";
}

int main() {

	solve();
}