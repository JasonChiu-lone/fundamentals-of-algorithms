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

int split_1(int N, int K, int current_segs, int min_s){
    if (N > min_s) return 0;
    if (current_segs > K) return 0;
    if (K == current_segs) return 1;
    
    // N划分成K个正整数之和的划分数目
    int ret = 0;
    for (int s = min_s; s <= N; s++){
        if (s == 0)
            continue;
        else
            ret += split_1(N-s, K, current_segs+1, s);
    }
    return ret;
}

int split_2(int n, int min_s){
    // N划分成若干个不同正整数之和的划分数目
    if (n == 0) return 1;
    if (n == min_s) return 1;
    int ret = 0;
    for (int s = min_s+1; s <= n; s++){
        ret += split_2(n-s, s);
    }
    return ret;
}

int split_3(int n, int min_s){
    // N划分成若干个奇正整数之和的划分数目
    if (n == 0) return 1;
    if (n == min_s) return 1;
    if (n < min_s) return 0;
    int ret = 0;
    for (int s = min_s; s <= n; s+=2){
        ret += split_3(n-s, s);
    }
    return ret;
}

int main(){
    int N, K;
    while (cin >> N >> K){
        cout << split_1(N, K, 0, 0) << endl;
        cout << split_2(N, 0) << endl;
        cout << split_3(N, 1) << endl;
    }
    return 0;
}