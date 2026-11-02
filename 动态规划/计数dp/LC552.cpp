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
constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int checkRecord(int n) {
        std::vector dp(n + 1, std::vector (2, std::vector<i64>(3 , 0ll)));
        dp[0][0][0] = 1;
        
        i64 ans = 0;
        for(i64 i = 1;i <= n;i ++) {
            // 选到场
            for(i64 j = 0;j <= 1;j ++) {
                for(i64 k = 0;k <= 2; k ++) {
                    dp[i][j][0] = (dp[i][j][0] % mod + dp[i - 1][j][k]) % mod;
                }
            }
            // 选缺勤
            for(i64 k = 0;k <= 2;k ++) {
                dp[i][1][0] = (dp[i][1][0] % mod + dp[i - 1][0][k]) % mod;
            }
            // 选迟到
            for(i64 j = 0;j <= 1;j ++) {
                for(i64 k = 1; k <= 2;k ++){
                    dp[i][j][k] = (dp[i][j][k] % mod + dp[i - 1][j][k - 1]) % mod;
                }
            }
        }
        for(i64 j = 0;j <= 1;j ++) {
            for(i64 k = 0;k <= 2; k ++)ans = (ans % mod + dp[n][j][k]) % mod;
        }
        
        return ans % mod;
    }
};