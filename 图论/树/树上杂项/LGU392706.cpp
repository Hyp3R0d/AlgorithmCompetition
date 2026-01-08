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


i64 p[maxn];
i64 dep[maxn], maxdep[maxn];
int main() {
	i64 n; std::cin >> n;
	std::vector<std::vector<pair<i64, i64>>>g(n + 1);
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	std::vector dp(n + 1, std::vector<i64>(4, 0));
	std::function<void(i64, i64, i64)>dfs = [&](i64 u, i64 f, i64 d) {
		dep[u] = d; maxdep[u] = dep[u];
		for (auto [v, w] : g[u]) {
			if (v == f)continue;
			dfs(v, u, d + w);
			maxdep[u] = std::max(maxdep[u], maxdep[v]);
			if (maxdep[v] - dep[u] >= dp[u][1]) {
				dp[u][2] = dp[u][1];
				dp[u][1] = maxdep[v] - dep[u];
				p[u] = v;
			} else if (maxdep[v] - dep[u] >= dp[u][2]) {
				dp[u][2] = maxdep[v] - dep[u];
			} else {
				continue;
			}
		}
	};
	dfs(1, 0, 0);
	i64 a = inf, ans = 0;
	std::function<void(i64, i64)>dfs2 = [&](i64 u, i64 f) {
		if (max(dp[u][1], dp[u][3]) < a) {
			a = std::max(dp[u][1], dp[u][3]);
			ans = u;
		}
		for (auto [v, w] : g[u]) {
			if (v == f)continue;
			if (v == p[u]) {
				dp[v][3] = std::max(dp[u][2], dp[u][3]) + w;
			} else {
				dp[v][3] = std::max(dp[u][1], dp[u][3]) + w;
			}
			dfs2(v, u);
		}
	};
	dfs2(1, 0);
	std::vector<i64>res;
	for (i64 i = 1; i <= n; i++) {
		if (std::max(dp[i][1], dp[i][3]) == a) {
			res.push_back(i);
		}
	}
	std::sort(res.begin(), res.end());
	for (i64 i = 0; i < res.size(); i++)std::cout << res[i] << "\n";
	return 0;
}