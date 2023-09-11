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


#define MAXN 1025

int d, n;
int v[MAXN][MAXN];


struct Point{
    int x, y, t;
    Point(){}
    Point(int x, int y, int t): x(x), y(y), t(t){}
} p[50];

int main(){
    cin >> d;
    cin >> n;
    int x, y, t;
    memset(v, 0, sizeof(v));
    for (int i = 0; i < n; i++){
        cin >> x >> y >> t;
        p[i] = Point(x, y, t);
    }
    // 枚举每个点附近半径为d的空间
    for (int m = 0; m < n; m++){
        Point &pt = p[m];
        for (int i = pt.x-d; i <= pt.x+d; i++){
            if (i < 0 || i >= MAXN) continue;
            for (int j = pt.y-d; j <= pt.y+d; j++){
                if (j < 0 || j >= MAXN) continue;
                v[i][j] += pt.t;
            }
        }
    }
    int v_[MAXN*MAXN];
    memcpy(v_, v, sizeof(v));
    sort(v_, v_+MAXN*MAXN);
    
    cout << count(v_, v_+MAXN*MAXN, v_[MAXN*MAXN-1]) << " " << v_[MAXN*MAXN-1] << endl;
    return 0;
}