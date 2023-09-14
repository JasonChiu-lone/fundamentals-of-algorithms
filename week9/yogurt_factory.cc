// POJ 2393

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

#define MAXN 10000
int C[MAXN]; // production cost per unit for each week
int Y[MAXN]; // demand for each week
int N; // N weeks
int S; // cost of storage per unit per week
int W[MAXN]; // production from W[j] is going to supply demands in week i // not necessary

int main(){
    memset(C, 0, sizeof(C));
    memset(Y, 0, sizeof(Y));
    memset(W, 0, sizeof(W));
    cin >> N >> S;
    for (int i = 0; i < N; i++){
        cin >> C[i] >> Y[i];
    }
    // 更新C为该周可得最低成本，用新数组标记每周的产品该由哪周来生产
    for (int i = 0; i < N; i++){
        for (int j = i; j < N; j++){
            // C[j] = min(C[j], C[i] + (j - i) * S);
            if (C[j] <= C[i] + (j - i) * S){
                W[j] = W[j] ? W[j] : j; // not necessary
            }
            else {
                W[j] = i; // not necessary
                C[j] = C[i] + (j - i) * S;
            }
        }
    }
    // output answer
    long long ans = 0;
    for (int i = 0; i < N; i++){
        ans += C[i] * Y[i];
    }
    cout << ans << endl;
    return 0;
}