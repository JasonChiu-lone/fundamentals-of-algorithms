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

#define MAXN 200000
#define MAX_STEP 5000

// bool accessible[MAX_STEP][MAXN];
bool **accessible = new bool*[MAX_STEP];


int main(){
    for(int i = 0; i < MAX_STEP; i++)
        accessible[i] = new bool[MAXN];
    int N, K;
    cin >> N >> K;
    if (N >= K){
        cout << N-K << endl;
        return 0;
    }
    accessible[0][N] = true;
    for (int step = 1; step < MAX_STEP; step++){
        if (accessible[step-1][K]){
            cout << step - 1 << endl;
            return 0;
        }
        for (int i = 0; i < MAXN; i++){
            if (accessible[step-1][i]){
                accessible[step][i] = true;
                // cout << i << " is accessible" << endl;
                if (i > 0) {
                    accessible[step][i-1] = true;
                    // cout << i-1 << " is accessible" << endl;
                }
                if (i+1 < MAXN) {
                    accessible[step][i+1] = true; 
                    // cout << i+1 << " is accessible" << endl;
                }
                if (i*2 < MAXN) {
                    accessible[step][2*i] = true; 
                    // cout << 2*i << " is accessible" << endl;
                }
            }
        }
    }
    return 0;
}