#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

#define MAXN 21
#define u 1
#define d 0

long long dp[MAXN+1][MAXN+1][2];
// dp[i][j][k]表示用i个木板排出栅栏，最左边的是其中第j矮的木板，k=0/1分别表示第二块木板比第一块木板短/长（i<=N, j<=N, k=0/1），此种状态下的方案数
// 状态转移方程见：https://luckyglass.github.io/2019/OldVer31/

int used[MAXN+1];
int a[MAXN+1];

void solve(int N, long long C){
    long long skipped = 0;
    for (int i = 1; i <= N; i++){
        int k = 0;
        for (int j = 1; j <= N; j++){
            skipped = 0;
            if (!used[j]){
                k++;
                if (i == 1)
                    skipped = dp[N][k][u] + dp[N][k][d];
                else{
                    if (a[i-1] < j && (i <= 2 || a[i-2] > a[i-1])){
                        skipped = dp[N-i+1][k][d];
                    }
                    else if (a[i-1] > j && (i <= 2 || a[i-2] < a[i-1])){
                        skipped = dp[N-i+1][k][u];
                    }
                }
                if (skipped >= C){
                    used[j] = true;
                    a[i] = j;
                    break;
                }
                else {
                    C -= skipped;
                }
            }
        }
    }
}

int main(){
    int K;
    cin >> K;

    // 先把dp解出来
    // 初始化
    memset(dp, 0, sizeof(dp));
    dp[1][1][u] = 1;
    dp[1][1][d] = 1;
    for (int i = 2; i <= MAXN; i++){
        for (int j = 1; j <= MAXN; j++){
            // dp[i][j][u] = sum dp[i-1][k][d], j <= k < i
            for (int k = j; k < i; k++){
                dp[i][j][u] += dp[i-1][k][d];
            }
            // dp[i][j][d] = sum dp[i-1][k][u], 1 <= k < j
            for (int k = 1; k < j; k++){
                dp[i][j][d] += dp[i-1][k][u];
            }
        }
    }


    while (K--){
        int N;
        cin >> N;
        long long C;
        cin >> C;

        memset(a, 0, sizeof(a));
        memset(used, 0, sizeof(used));
        solve(N, C);
        for (int i = 1; i <= N; i++)
            cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}