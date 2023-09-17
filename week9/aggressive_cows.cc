// POJ 2456

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
#include <stdio.h>
using namespace std;

#define MAXN 100000
int x[MAXN], N, C;

int verify(int max_d){
    int cnt = 1;
    int last_x = x[0];
    for (int i = 1; i < N; i++){
        if (x[i] - last_x >= max_d){
            cnt++;
            last_x = x[i];
        }
    }
    if (cnt >= C) return 1;
    else return 0;
}

int main(){
    memset(x, -1, sizeof(x));
    int tmp;
    cin >> N >> C;
    for(int i = 0; i < N; i++){
        scanf("%d", &x[i]);
    }
    sort(x, x+N);
    // 首先猜一个max_d，通过二分搜索找到合适的max_d
    int l = 1;
    int r = x[N-1];
    while(r-l > 1){
        int mid = (r+l) / 2;
        if (verify(mid)) l = mid;
        else r = mid;
    }
    printf("%d\n", l);
    return 0;
}