// POJ 4001
/***
 * 农夫知道一头牛的位置，想要抓住它。农夫和牛都位于数轴上，农夫起始位于点N(0<=N<=100000)，牛位于点K(0<=K<=100000)。农夫有两种移动方式：

1、从X移动到X-1或X+1，每次移动花费一分钟
2、从X移动到2*X，每次移动花费一分钟

假设牛没有意识到农夫的行动，站在原地不动。农夫最少要花多少时间才能抓住牛？
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 200000
int a[MAXN];


int main(){
    int N, K;
    cin >> N >> K;
    if (N >= K){
        cout << N - K << endl;
        return 0;
    }
    memset(a, 0, sizeof(a));
    a[N] = 1;
    for (int t = 1; ; t++){
        if (a[K]){
            cout << a[K]-1 << endl;
            break;
        }

        for (int i = 0; i < 2*max(N, K); i++){
            if (a[i] == t){
                if (i > 0){
                    a[i-1] = min(t+1, a[i-1]?a[i-1]:MAXN);
                }
                if (i+1 < 2*max(N, K)){
                    a[i+1] = min(t+1, a[i+1]?a[i+1]:MAXN);
                }
                if (i*2 < 2*max(N, K)){
                    a[i*2] = min(t+1, a[i*2]?a[i*2]:MAXN);
                }
            }
        }
    }
    return 0;
}