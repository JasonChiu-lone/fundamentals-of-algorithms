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