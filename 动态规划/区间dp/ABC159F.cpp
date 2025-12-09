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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


// 0 - 1 背包 + 贡献法
int main() {
    i64 N, S; std::cin >> N >> S;
    std::vector<i64>A(N + 1);
    for (i64 i = 1; i <= N; i++)std::cin >> A[i];
    std::vector<i64>total(S + 1);
    //total[0] = 1;
    std::vector dp(N + 1, std::vector<i64>(S + 1));
    i64 ans = 0;
    for (i64 i = 1; i <= N; i++) {

        std::vector<i64>dp(S + 1);

        for (i64 j = S; j >= A[i]; j--) {
            dp[j] = (dp[j] % mod + total[j - A[i]]) % mod;
        }
        if (S >= A[i])
            dp[A[i]] = (dp[A[i]] % mod + i) % mod;
        for (i64 j = A[i]; j <= S; j++) {
            total[j] = (total[j] % mod + dp[j]) % mod;
        }

        ans = (ans % mod + dp[S] % mod * (N - i + 1) % mod) % mod;

    }
    std::cout << ans % mod << "\n";
}