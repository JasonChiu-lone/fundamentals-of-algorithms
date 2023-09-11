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

int split(int n, int min_s){
    if (n == 0) return 1;
    if (n == min_s) return 1;
    int ret = 0;
    for (int s = min_s; s <= n; s++){
        ret += split(n-s, s);
    }
    return ret;
}

int main(){
    int N;
    while(cin>>N){
        cout << split(N, 1) << endl;
    }
    return 0;
}