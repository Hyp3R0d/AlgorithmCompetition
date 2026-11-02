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

struct sq {
	i64 u; i64 dis;
	bool operator<(const sq&b)const {
		return dis > b.dis;
	}
};
class Solution {
public:
	vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
		std::vector<std::vector<pair<i64, i64>>>g(n);
		for(i64 i = 0;i < edges.size(); i ++) {
			i64 x = edges[i][0], y = edges[i][1];
			g[x].push_back({y, i});
			g[y].push_back({x, i});
		}
		i64 dis[n][2], delta, vis[n];
		memset(dis, 0x3f, sizeof(dis));
		dis[source][0] = dis[source][1] = 0;
		priority_queue<sq>pq;
		auto dijkstra = [&](i64 k) {
			memset(vis, 0 ,sizeof(vis));
			while(pq.size())pq.pop();
			pq.push({0, 0});
			while(pq.size()) {
				auto [x, d] = pq.top();
				pq.pop(); if(vis[x]) continue;
				vis[x] = 1;
				if(x == destination) return;
				for(auto [y , id] : g[x]) {
					i64 wt = edges[id][2];
					if(wt == -1) wt = 1;
					if(k == 1 and edges[id][2] == -1) {
						i64 w = delta + dis[y][0] - dis[x][1];
						if(w > wt) edges[id][2] = wt = w;
					}
                    if(dis[y][k] > dis[x][k] + wt) {
					dis[y][k] = std::min(dis[y][k], dis[x][k] + wt);
                        if(not vis[y])
                        pq.push({y, dis[y][k]});
                    }
				}
			}
		};
		dijkstra(0);
		delta = target - dis[destination][0];
		if(delta < 0) return {};
		dijkstra(1);
		if(dis[destination][1] < target)return {};
		for(auto &e : edges) {
			if(e[2] == -1)e[2] = 1;
		}
		return edges;
	}
};