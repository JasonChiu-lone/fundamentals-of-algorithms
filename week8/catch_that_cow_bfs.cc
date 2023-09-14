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

#define MAXL 200001

int main(){
    int N, K;
    cin >> N >> K;
    int a[MAXL];
    memset(a, -1, sizeof(a));
    a[N] = 0;
    int d[3];
    // 关键思想：队列
    queue<int> q; q.push(N);
    while(a[K] == -1){
        d[0] = q.front() - 1;
        d[1] = d[0] + 2;
        d[2] = (d[0] + 1) * 2;
        q.pop();
        for(int i = 0; i < 3; i++){
            if (d[i] >= 0 && d[i] < MAXL && a[d[i]] == -1){
                a[d[i]] = a[d[0]+1]+1;
                // cout << "a[" << d[i] << "]=" << a[d[0]+1] << endl; 
                q.push(d[i]);
            }
        }
    }
    cout << a[K] << endl;
    return 0;
}