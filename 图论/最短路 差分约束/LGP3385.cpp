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

constexpr i64 mod = 1e5 + 3;
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct edge {
	i64 u, v, w, nxt;
};

void solve() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>dis(n + 1, inf);
	i64 cnt = 0; std::vector<i64>head(n + 1, -1);
	std::vector<edge>e(2 * m + 1);
	auto addEdge = [&](i64 u, i64 v, i64 w) {
		e[cnt].u = u; e[cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u];
		head[u] = cnt++;
	};
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		if (w >= 0)addEdge(u, v, w), addEdge(v, u, w);
		else addEdge(u, v, w);
	}
	queue<i64>q; q.push(1); dis[1] = 0;
	std::vector<i64>vis(n + 1); vis[1] = true;
	std::vector<i64>dep(n + 1);
	while (q.size()) {
		auto u = q.front(); q.pop();
		vis[u] = false;
		for (i64 g = head[u]; g != -1; g = e[g].nxt) {
			i64 v = e[g].v, w = e[g].w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				dep[v] = dep[u] + 1;
				if (dep[v] >= n) {
					puts("YES"); return;
				}
				if (not vis[v]) {
					q.push(v); vis[v] = true;
				}
			}
		}
	}
	puts("NO");
	return;
}


int main() {
	i64 T; std::cin >> T;
	while (T--) solve();
}