// POJ1042

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <array>
#include <stdio.h>
using namespace std;

#define MAXN 25

int h; 
int n; 
int t[MAXN-1]; 
int f[MAXN]; 
int d[MAXN]; 
int max_fish;
array<int , MAXN> ans;

int sum(int *begin, int *end){
    int sum = 0;
    while(begin != end){
        sum += *begin;
        begin++;
    }
    return sum;
}

int max(int *begin, int *end){
    int max = -1;
    while (begin != end){
        max = *begin > max ? *begin : max;
        begin++;
    }
    return max;
}


void fish(int available_intervals, int last_lake){
    if (available_intervals <= 0)
        return;
    array<int, MAXN> current_ans; current_ans.fill(0);
    int current_fish = 0;
    int intervals_left = available_intervals;
    int v[MAXN];
    memcpy(v, f, sizeof(f));
    while(intervals_left){ 
        int max_v = 0;
        int current_lake = 0;
        for (int i = 0; i <= last_lake; i++){
            if (v[i] > max_v){
                max_v = v[i];
                current_lake = i;
            }
        }
        current_fish += max_v;
        v[current_lake] = max(0, v[current_lake] - d[current_lake]);
        current_ans[current_lake] ++;
        intervals_left--;
    }
    if (max_fish == 0 || current_fish > max_fish){ 
        max_fish = current_fish;
        ans = current_ans;
    }
}

int main(){
    cin >> n;
    while (n){
        ans.fill(0);
        max_fish = 0;
        cin >> h;
        for (int i = 0; i < n; i++)
            cin >> f[i];
        for (int i = 0; i < n; i++)
            cin >> d[i];
        for (int i = 0; i < n-1; i++)
            cin >> t[i];
        for (int j = 0; j < n; j++){
            fish(12 * h - sum(t, t+j), j);
        }
        // print answer
        cout << ans[0] * 5;
        for (int i = 1; i < n; i++)
            cout << ", " << ans[i] * 5;
        cout << endl;
        cout << "Number of fish expected: " << max_fish << endl << endl;

        cin >> n;
    }
    return 0;
}
// POJ1042

#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <array>
using namespace std;

#define MAXN 25

int h; // available hours
int n; // # of lakes along a single, one-way road
int t[MAXN-1]; // # of 5-minute intervals to travel from lake i to lake i+1
int f[MAXN]; // # of fish to be caught within the first 5 minutes
int d[MAXN]; // drop rate per 5 minutes
int max_fish;
array<int , MAXN> ans;

int sum(int *begin, int *end){
    int sum = 0;
    while(begin != end){
        sum += *begin;
        begin++;
    }
    return sum;
}

int max(int *begin, int *end){
    int max = -1;
    while (begin != end){
        max = *begin > max ? *begin : max;
        begin++;
    }
    return max;
}


void fish(int available_intervals, int last_lake){
    if (available_intervals <= 0)
        return;
    // 贪心选择出鱼最多的池塘
    array<int, MAXN> current_ans; current_ans.fill(0);
    int current_fish = 0;
    int intervals_left = available_intervals;
    int v[MAXN];
    memcpy(v, f, sizeof(f));
    while(intervals_left){ // 还剩时间
        int max_v = 0;
        int current_lake = 0;
        // 找到最大v的池塘，默认0
        for (int i = 0; i <= last_lake; i++){
            if (v[i] > max_v){
                max_v = v[i];
                current_lake = i;
            }
        }
        // 在这钓鱼
        current_fish += max_v;
        v[current_lake] = max(0, v[current_lake] - d[current_lake]);
        current_ans[current_lake] ++;
        intervals_left--;
    }
    if (max_fish == 0 || current_fish > max_fish){ // [fix]至少要有一个答案
        max_fish = current_fish;
        ans = current_ans;
    }
}

int main(){
    cin >> n;
    while (n){
        ans.fill(0);
        max_fish = 0;
        cin >> h;
        for (int i = 0; i < n; i++)
            cin >> f[i];
        for (int i = 0; i < n; i++)
            cin >> d[i];
        for (int i = 0; i < n-1; i++)
            cin >> t[i];
        // 将全过程分为钓鱼的过程和移动的过程
        // 首先枚举以池塘0~池塘n-1作为最后一个池塘j所需要花费的时间，这样移动可以认为是瞬间发生，接下来贪心求出池塘0~池塘j所能钓到的最多数量
        for (int j = 0; j < n; j++){ // 枚举终点
            fish(12 * h - sum(t, t+j), j);
        }
        // print answer
        cout << ans[0] * 5;
        for (int i = 1; i < n; i++)
            cout << ", " << ans[i] * 5;
        cout << endl;
        cout << "Number of fish expected: " << max_fish << endl << endl;

        cin >> n;
    }
    return 0;
}