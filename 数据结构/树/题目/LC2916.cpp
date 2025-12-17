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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    struct SegmentTree {
    public:
        struct Node {
        public:
            i64 l; i64 r; i64 sum; i64 sumSquare; i64 lazyTag;
        };
        std::vector<Node>tr;
        SegmentTree(i64 n): tr(4 * n + 3) {}
        void pushUp(i64 u) {
            tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
            tr[u].sum %= mod;
            tr[u].sumSquare = tr[u << 1].sumSquare + tr[u << 1 | 1].sumSquare;
            tr[u].sumSquare %= mod;
        }
        void build(i64 u, i64 l, i64 r) {
            tr[u].l = l; tr[u].r = r;
            tr[u].lazyTag = 0;
            if (l == r) {
                tr[u].sum = 0; tr[u].sumSquare = 0;
                return;
            }
            i64 mid = (l + r) >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushUp(u);
        }
        void pushDown(i64 u) {
            if (tr[u].lazyTag) {
                i64 add = tr[u].lazyTag;
                tr[u].lazyTag = 0;
                tr[u << 1].lazyTag = (tr[u << 1].lazyTag + add) % mod;
                tr[u << 1 | 1].lazyTag = (tr[u << 1 | 1].lazyTag + add) % mod;
                i64 len1 = (tr[u << 1].r - tr[u << 1].l + 1);
                i64 len2 = (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1);
                tr[u << 1].sumSquare = (tr[u << 1].sumSquare + 2 * add % mod * tr[u << 1].sum % mod) % mod;
                tr[u << 1].sumSquare += len1 * add * add;
                tr[u << 1].sumSquare %= mod;
                tr[u << 1].sum = (tr[u << 1].sum + len1 * add) % mod;
                tr[u << 1 | 1].sumSquare = (tr[u << 1 | 1].sumSquare + 2 * add * tr[u << 1 | 1].sum) % mod;
                tr[u << 1 | 1].sumSquare += len2 * add * add;
                tr[u << 1 | 1].sumSquare %= mod;
                tr[u << 1 | 1].sum = (tr[u << 1 | 1].sum + len2 * add) % mod;
            }
        }
        void modify1(i64 u, i64 l, i64 r, i64 v) {
            if (tr[u].l >= l and tr[u].r <= r) {
                i64 len = (tr[u].r - tr[u].l + 1);
                tr[u].sumSquare = (tr[u].sumSquare + len * v * v % mod + tr[u].sum * 2 % mod * v) % mod;
                tr[u].sum += len * v;
                tr[u].sum %= mod;
                tr[u].lazyTag += v;
                tr[u].lazyTag %= mod;
                return;
            }
            pushDown(u);
            i64 mid = (tr[u].l + tr[u].r) >> 1;
            if (l <= mid)modify1(u << 1, l, r, v);
            if (r > mid)modify1(u << 1 | 1, l, r, v);
            pushUp(u);
        }
        i64 query1(i64 u, i64 l, i64 r) {
            i64 ret = 0;
            if (tr[u].l >= l and tr[u].r <= r) {
                return tr[u].sum % mod;
            }
            pushDown(u);
            i64 mid = (tr[u].l + tr[u].r) >> 1;
            if (l <= mid)ret = (ret % mod + query1(u << 1, l, r)) % mod;
            if (r > mid)ret = (ret % mod + query1(u << 1 | 1, l, r)) % mod;
            return ret;
        }
        i64 query2(i64 u, i64 l, i64 r) {
            i64 ret = 0;
            if (tr[u].l >= l and tr[u].r <= r) {
                return tr[u].sumSquare % mod;
            }
            pushDown(u);
            i64 mid = (tr[u].l + tr[u].r) >> 1;
            if (l <= mid)ret = (ret % mod + query2(u << 1, l, r)) % mod;
            if (r > mid)ret = (ret % mod + query2(u << 1 | 1, l, r)) % mod;
            return ret;
        }
    };
    int sumCounts(vector<int>& nums) {
        i64 n = nums.size();
        SegmentTree t(n);
        t.build(1, 1, n);
        i64 ans = 0;
        std::unordered_map<i64, i64>pre;
        for (i64 i = 1; i <= n; i++) {
            i64 p = pre[nums[i - 1]];
            t.modify1(1, p + 1, i, 1);
            ans = (ans % mod + t.query2(1, 1, n)) % mod;
            pre[nums[i - 1]] = i;
        }
        return ans % mod;
    }
};
