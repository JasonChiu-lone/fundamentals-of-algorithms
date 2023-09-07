// POJ1416

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

int digits[6];
int target;
int num;
int len;
int dp[6][7];

vector<pair<int, pair<vector<int>, vector<int> > > > solutions;

void print_solutions(){
    for (int i = 0; i < solutions.size(); i++){
        cout << "sum=" << solutions[i].first << ": " << endl;
        for (int j = 0; j < solutions[i].second.first.size(); j++){
            cout << "\ti=" << solutions[i].second.first[j] << " j=" << solutions[i].second.second[j] << endl;
        }
        cout << endl;
    }
}

// # # # # # #
// 0 1 2 3 4 5
void solve(vector<int> i, vector<int> j, int sum){
    cout << "last i=" << *i.rbegin() << " last j=" << *j.rbegin() << " sum=" << sum << endl;
    if (sum > target) return;
    if (*i.rbegin() + *j.rbegin() == len){
        if (sum <= target)
            solutions.push_back(make_pair(sum, make_pair(i, j)));
        return;
    }
    int k = *i.rbegin() + *j.rbegin();
    for (int l = 1; k + l <= len; l++){
        vector<int> new_i = i;
        new_i.push_back(k);
        vector<int> new_j = j;
        new_j.push_back(l);
        solve(new_i, new_j, sum + dp[k][l]);
    }
}

int main(){
    
    while (cin >> target >> num && (target || num)){
        memset(digits, 0, sizeof(digits));
        solutions = vector<pair<int, pair<vector<int>, vector<int> > > > ();
        char c[7];
        sprintf(c, "%d", num);
        for (int d = 0; ; d++){
            if (c[d] == 0){
                len = d;
                break;
            }
            digits[d] = c[d] - '0';
        }
        
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < 6; i++){
            dp[i][1] = digits[i]?digits[i]:1000000000;
            for (int j = 2; j <= 6-i; j++){
                dp[i][j] = dp[i][j-1] * 10 + digits[i+j-1];
            }
        }
        vector<int> i;
        vector<int> j;
        i.push_back(0);
        j.push_back(0);
        solve(i, j, 0);
        print_solutions();
        sort(solutions.begin(), solutions.end());
        if (solutions.size() == 0){
            cout << "error" << endl;
        } else {
            if
        }
        system("pause");
    }
    return 0;
}

// num = 12345
// digits = {0, 5, 4, 3, 2, 1}

// dp[i][j] = value of substr(num, i, j)