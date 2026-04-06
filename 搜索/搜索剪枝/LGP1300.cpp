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

constexpr i64 mod = 45989;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


// 0 北 1 西 2 南 3 东

bool vis[45][45][45]; // 坐标, 方向
std::vector<pair<i64, i64>>rev = {{ -1, 0}, {0, -1}, {1, 0}, {0, 1}};

i64 ans = inf;
string g[30];
int main() {
	i64 h, w; std::cin >> h >> w;
	for (i64 i = 1; i <= h; i++) {
		std::cin >> g[i]; g[i] = " " + g[i];
	}
	i64 sx, sy, tx, ty; i64 dir = 0;
	for (i64 i = 1; i <= h; i++) {
		for (i64 j = 1; j <= w; j++) {
			if (isalpha(g[i][j])) {
				if (g[i][j] == 'F') {
					tx = i; ty = j;
				} else {
					sx = i, sy = j;
					if (g[i][j] == 'N') {
						dir = 0;
					} else if (g[i][j] == 'W') {
						dir = 1;
					} else if (g[i][j] == 'S') {
						dir = 2;
					} else dir = 3;
				}
			}
		}
	}
	std::function<void(i64, i64, i64, i64)>dfs = [&](i64 x, i64 y, i64 dir, i64 d) {

		if (d >= ans) {
			return;
		} // 剪枝
		if (x == tx and y == ty) {
			ans = std::min(ans, d);
			return;
		}
		vis[x][y][dir] = 1;
		i64 tmp = dir;
		// 试试直走
		bool f = false;
		auto [dx, dy] = rev[tmp];
		i64 xx = x + dx, yy = y + dy;
		if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
			f = true;
			if (not vis[xx][yy][tmp] and d < ans)
				dfs(xx, yy, tmp, d);
		}
		tmp = (dir + 1) % 4;// 试试左转
		dx = rev[tmp].first, dy = rev[tmp].second;
		xx = x + dx, yy = y + dy;
		if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
			f = true;
			if (not vis[xx][yy][tmp] and d + 1 < ans) //剪枝
				dfs(xx, yy, tmp, d + 1);
		}
		tmp = (dir - 1 + 4) % 4; // 试试右转
		dx = rev[tmp].first, dy = rev[tmp].second;
		xx = x + dx, yy = y + dy;
		// 右转
		if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
			f = true;
			if (not vis[xx][yy][tmp] and d + 5 < ans)
				dfs(xx, yy, tmp, d + 5);
		}
		if (not f) {
			tmp = (dir + 2) % 4;// 前后右 都不能, 试试向后转
			dx = rev[tmp].first, dy = rev[tmp].second;
			xx = x + dx, yy = y + dy;
			if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
				if (not vis[xx][yy][tmp] and d + 10 < ans) // 剪枝
					dfs(xx, yy, tmp, d + 10);
			}
		}
		vis[x][y][dir] = false; // 回溯
	};
	dfs(sx, sy, dir, 0);
	std::cout << ans << "\n";
	return 0;
}


/*记忆化搜索*/
#include <bits/extc++.h>

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

int main() {
  i64 h, w;
  std::cin >> h >> w;
  std::vector<string> g(h + 1);
  for (i64 i = 1; i <= h; i++) {
    std::cin >> g[i];
    g[i] = " " + g[i];
  }
  i64 dir = 0;
  // 0:N 1:E 2:S 3:W
  std::vector<std::pair<i64, i64>> Dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  i64 sx = -1, sy = -1;
  i64 tx = -1, ty = -1;
  for (i64 i = 1; i <= h; i++) {
    for (i64 j = 1; j <= w; j++) {
      if (g[i][j] != '.' and g[i][j] != '#' and g[i][j] != 'F') {
        sx = i;
        sy = j;
        if (g[i][j] == 'N')
          dir = 0;
        else if (g[i][j] == 'E')
          dir = 1;
        else if (g[i][j] == 'S')
          dir = 2;
        else if (g[i][j] == 'W')
          dir = 3;
      } else if (g[i][j] == 'F') {
        tx = i;
        ty = j;
      }
    }
  }
  std::vector dp(h + 1, std::vector(w + 1, std::vector<i64>(5, -1)));
  std::function<i64(i64, i64, i64)> dfs = [&](i64 x, i64 y, i64 curdir) {
    if (x == tx and y == ty) {
      return dp[x][y][curdir] = 0;
    }
    if (dp[x][y][curdir] != -1)
      return dp[x][y][curdir];
    dp[x][y][curdir] = inf;
    auto [dx, dy] = Dir[curdir];
    i64 xx = x + dx, yy = y + dy;
    bool flag = false;
    if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
      dp[x][y][curdir] = std::min(dp[x][y][curdir], dfs(xx, yy, curdir));
      flag = true;
    }
    i64 tmp = (curdir - 1 + 4) % 4;
    dx = Dir[tmp].first, dy = Dir[tmp].second;
    xx = x + dx, yy = y + dy;
    if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
      dp[x][y][curdir] = std::min(dp[x][y][curdir], dfs(xx, yy, tmp) + 1);
      flag = true;
    }
    tmp = (curdir + 1) % 4;
    dx = Dir[tmp].first, dy = Dir[tmp].second;
    xx = x + dx, yy = y + dy;
    if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
      dp[x][y][curdir] = std::min(dp[x][y][curdir], dfs(xx, yy, tmp) + 5);
      flag = true;
    }
    if (not flag) {
      tmp = (curdir + 2) % 4;
      dx = Dir[tmp].first, dy = Dir[tmp].second;
      xx = x + dx, yy = y + dy;
      if (xx >= 1 and xx <= h and yy >= 1 and yy <= w and g[xx][yy] != '.') {
        dp[x][y][curdir] = std::min(dp[x][y][curdir], dfs(xx, yy, tmp) + 10);
      }
    }
    return dp[x][y][curdir];
  };
  std::cout << dfs(sx, sy, dir);
}
