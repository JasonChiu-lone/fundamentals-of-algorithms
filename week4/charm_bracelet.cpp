// http://bailian.openjudge.cn/practice/4131/

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

#define MAXN 3500
#define MAXM 13000
using namespace std;

int main(){
    int N, M;
    int w[MAXN], d[MAXN];
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        cin >> w[i] >> d[i];
    }
    // max(∑d) s.t. ∑w <= M
    int dp[MAXM];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < N; i++){
        // 将前i件物品装入最大容量为j的背包所能取得的最大价值dp[i][j]为：
        // 1）不装入第i件物品
        // 2）装入第i件物品（如果能装下）
        // 中的最大值
        // dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i])
        for (int j = M; j >= 0; j--){
            dp[j] = j>=w[i]?max(dp[j], dp[j-w[i]] + d[i]):dp[j];
        }
    }
    cout << dp[M] << endl;

    return 0;
}