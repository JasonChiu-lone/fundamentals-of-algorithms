// POJ: 1321

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

#define MAXN 8

char chess_board[MAXN][MAXN];
long long ans;
bool c[MAXN];
int n, k;

void dfs(int r, int k, int depth = 0){
    // cout << "dfs with r=" << r << " k=" << k << endl;
    if (k == 0) {
        ans ++;
        return;
    }
    for (int i = r; i < n; i++){
        for (int j = 0; j < n; j++){
            if (chess_board[i][j] == '.' || c[j])
                continue;
            // cout << "i=" << i <<" j="<<j << " k=" << k << " depth=" << depth<<endl;
            c[j] = true;
            dfs(i + 1, k - 1, depth+1);
            c[j] = false;
        }
    }
}

int main(){
    
    while (cin >> n >> k && n != -1 && k != -1){
        ans = 0;
        memset(chess_board, 0, sizeof(chess_board));
        memset(c, false, sizeof(c));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> chess_board[i][j];
            }
        }
        dfs(0, k);
        cout << ans << endl;
    }
    return 0;
}