// http://bailian.openjudge.cn/practice/1221/

// [解析](https://blog.csdn.net/wolfblood_zzx/article/details/9949269)

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

#define MAXN 255

unsigned long long sum(unsigned long long a[MAXN], int f, int t){
    unsigned long long ret = 0;
    for (int i = f; i <= t; i++)
        ret += a[i];
    return ret;
}

int main(){
    int N;
    cin >> N;
    while (N != 0){
        unsigned long long dp[MAXN][MAXN];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < MAXN; i++) dp[0][i] = 1;
        dp[1][1] = 1;
        for (int i = 2; i <= N; i++){
            for (int j = 1; j <= N / 2; j++){
                dp[i][j] = sum(dp[i-2*j], j, i-j);
            }
            dp[i][i] = 1;
        }
        cout << N << " " << sum(dp[N], 1, N) << endl;
        cin >> N;
    }
    return 0;
}