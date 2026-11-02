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
    int numberOfCombinations(string num) {
        i64 n = num.size();
        std::vector lcp(n + 2, std::vector<i64>(n + 2, 0ll));
        num = " " + num;
        if(num[1] == '0') return 0ll;
        for(i64 i = n;i >= 1;i --) {
          for(i64 j = n;j >= 1;j --) {
            if(num[i] == num[j]) {
              lcp[i][j] = lcp[i + 1][j + 1] + 1;
            }
          }
        }
        
        std::vector dp(n + 1,std::vector<i64>(n + 1, 0ll));
        // 新增：sum_dp[len][end] 表示以 end 结尾，且长度 <= len 的方案数总和
        std::vector sum_dp(n + 1,std::vector<i64>(n + 1, 0ll)); 
        
        for(i64 j = 1; j <= n; j ++) { 
          // 内层倒序遍历 i，这样当前数字长度 L = j - i + 1 是从 1 逐渐递增的，方便顺手维护前缀和
          for(i64 i = j; i >= 1; i --) {
            if(i == 1) {
                dp[i][j] = 1;
            } else if(num[i] != '0') {
                i64 L = j - i + 1; 
                
                // 1. 上一个数字长度严格小于 L 的所有方案和 (O(1) 获取)
                dp[i][j] = sum_dp[L - 1][i - 1]; 
                
                // 2. 上一个数字长度刚好等于 L 的方案 (单独拎出来判字典序)
                i64 k = i - L;
                if(k >= 1 and num[k] != '0') {
                    i64 len = lcp[k][i];
                    if(len >= L) {
                        dp[i][j] = (dp[i][j] % mod + dp[k][i - 1]) % mod;
                    } else if(num[k + len] < num[i + len]) {
                        dp[i][j] = (dp[i][j] % mod + dp[k][i - 1]) % mod;
                    }
                }
            }
            
            // 维护当前 j 结尾的 sum_dp 前缀和
            i64 L = j - i + 1;
            sum_dp[L][j] = (sum_dp[L - 1][j] + dp[i][j]) % mod;
          }
          
          // 对于大于 j 的长度限制，其方案数和长度为 j 的方案数一样（因为数字总长最多也就 j）
          for(i64 L = j + 1; L <= n; L ++) {
              sum_dp[L][j] = sum_dp[j][j];
          }
        }
        
        i64 ret = 0;
        for(i64 i = 1;i <= n;i ++) if(num[i] != '0')ret = (ret % mod + dp[i][n]) % mod;
        return ret % mod;
    }
};