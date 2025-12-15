// 自然溢出单哈希

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




// 双哈希

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
