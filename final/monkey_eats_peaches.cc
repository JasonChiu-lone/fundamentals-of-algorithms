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

int check(int N, int s){
    for (int n = 0; n < N; n++){
        if (s % (N-1)) return 0;
        s = s / (N-1) * N + 1;
    }
    return s;
}

int f(int N){
    // 枚举最后每份有多少个桃子
    int s = 1;
    while (true){
        // if s satisfies condition
        int ans = check(N, s*(N-1));
        if (ans){
            return ans;
        }
        else {
            s++;
        }
    }
    return 0;
}

int main(){
    int N;
    cin >> N;
    while (N){
        cout << f(N) << endl;
        cin >> N;
    }
    return 0;
}

// N=2:  7 3 1
// N=4:  253 189 141 106