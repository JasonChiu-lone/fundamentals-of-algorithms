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

#define MAXN 26
int chess[MAXN][MAXN];
int p, q; // p stands for numbers, q stands for letters

void print(int num, int let){
    cout << 'A' + let << '1' + num;
}

bool check(int paint[MAXN][MAXN]){
    bool ret = true;
    for (int i = 0; i < p; i++){
        for (int j = 0; j < p; j++){
            ret &= paint[i][j];
            if (!ret) return false;
        }
    }
    return ret;
}

bool dfs(int paint[MAXN][MAXN], int num, int let){
    if (num < 0 || let < 0 || num >= p || let >= q || paint[num][let])
        return false;
    paint[num][let] = 1;
    if (check(paint)){
        print(num, let);
        return true;
    }
    // lexicographically
    /*
    * A1 B1 ... N1
    * A2 B2 ... N2
    * ...
    * An Bn ... Nn
    */
    if (dfs(paint, num-1, let-2)){
        print(num, let);
        return true;
    }
}

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        
        cin >> p >> q;
        cout << "Scenario #" << n+1 << ":" << endl;
        memset(chess, 0, sizeof(chess));
        dfs(chess, 0, 0);
    }
    return 0;
}

for ()