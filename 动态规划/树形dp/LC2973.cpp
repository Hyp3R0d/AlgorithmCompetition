
/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/

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

class Solution {
public:
	vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
		i64 n = cost.size();
		cost.insert(cost.begin(), 0ll);
		std::vector<std::vector<i64>>g(n + 1);
		for (auto e : edges) {
			g[e[0] + 1].push_back(e[1] + 1);
			g[e[1] + 1].push_back(e[0] + 1);
		}
		std::vector pos(n + 1, std::vector<i64>(3, -inf));
		std::vector neg(n + 1, std::vector<i64>(3, -inf));
		std::vector<i64>ans(n);
		std::vector<i64>sz(n + 1, 1);
		std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
			if (cost[u] < 0)neg[u][0] = abs(cost[u]);
			else pos[u][0] = abs(cost[u]);
			for (auto v : g[u]) {
				if (v == f)continue;
				dfs(v, u);
				std::vector<i64>v1, v2;
				// 维护pos的三个最大值
				for (i64 i = 0; i <= 2; i++) {
					if (pos[v][i] != -inf) {
						v1.push_back(pos[v][i]);
					}
					if (pos[u][i] != -inf)v1.push_back(pos[u][i]);
					if (neg[v][i] != -inf) {
						v2.push_back(neg[v][i]);
					}
					if (neg[u][i] != -inf)v2.push_back(neg[v][i]);

				}
				sz[u] += sz[v];
				std::sort(v1.begin(), v1.end(), [&](i64 x, i64 y) {
					return abs(x) > abs(y);
				});
				std::sort(v2.begin(), v2.end(), [&](i64 x, i64 y) {
					return abs(x) > abs(y);
				});
				i64 idx1 = 0; i64 idx2 = 0;
				for (i64 i = 0; i < std::min(3ll, (i64)v1.size()); i++)pos[u][i] = v1[i];
				for (i64 i = 0; i < std::min(3ll, (i64)v2.size()); i++)neg[u][i] = v2[i];
			}
            if (sz[u] < 3)ans[u - 1] = 1;
				else {
					// 凑一正两负
					if (pos[u][0] != -inf and neg[u][0] != -inf and neg[u][1] != -inf)ans[u - 1] =
							(pos[u][0] * neg[u][0] * neg[u][1]);
					// 凑三正
                    else if (pos[u][0] != -inf and pos[u][1] != -inf and pos[u][2] != -inf)ans[u - 1] =
							(pos[u][0] * pos[u][1] * pos[u][2]);
                    else ans[u - 1] = 0;
				}
		};
		dfs(1, -1);
		return ans;
	}
};