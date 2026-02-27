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
const i64 maxn = 2e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
  i64 n, k;
  std::cin >> n >> k;
  std::vector<i64> a(n + 1);
  for (i64 i = 1; i <= n; i++)
    std::cin >> a[i];
  std::sort(a.begin() + 1, a.begin() + 1 + n);
  std::vector<i64> neg(1), pos(1);
  for (i64 i = 1; i <= n; i++) {
    if (a[i] < 0)
      neg.push_back(a[i]);
    else
      pos.push_back(a[i]);
  }
  i64 sz1 = neg.size() - 1, sz2 = pos.size() - 1;
  auto check = [&](i64 x) {
    i64 ans = 0;
    for (i64 i = 1; i <= sz1; i++) {
      i64 l = 1, r = sz2, idx = -1;
      while (l <= r) {
        i64 mid = (l + r) >> 1;
        if (neg[i] * pos[mid] <= x)
          r = mid - 1, idx = mid;
        else
          l = mid + 1;
      }
      if (idx != -1)
        ans += sz2 - idx + 1;
    }
    for (i64 i = sz1; i >= 1; i--) {
      i64 l = 1, r = i - 1, idx = -1;
      while (l <= r) {
        i64 mid = (l + r) >> 1;
        if (neg[i] * neg[mid] <= x)
          r = mid - 1, idx = mid;
        else
          l = mid + 1;
      }
      if (idx != -1)
        ans += std::max(0ll, i - idx);
    }
    for (i64 i = 1; i <= sz2; i++) {
      i64 l = i + 1, r = sz2, idx = -1;
      while (l <= r) {
        i64 mid = (l + r) >> 1;
        if (pos[i] * pos[mid] <= x) {
          l = mid + 1, idx = mid;
        } else
          r = mid - 1;
      }
      ans += std::max(0ll, idx - i);
    }
    return ans >= k;
  };
  i64 l = -1e18, r = 1e18;
  i64 ans = -1;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  std::cout << ans << "\n";
}
int main() { solve(); }
