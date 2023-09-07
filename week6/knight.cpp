/*** 
 * mem: 264KB
 * time: 12ms
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <stack>
#include <deque>
using namespace std;

#define MAXN 26
int p, q; // p numbers; q letters
bool chess[MAXN][MAXN];
// stack<string> ans;
deque<string> ans;

ostream &operator<<(ostream &os, deque<string> &q){
    deque<string>::iterator it = q.begin();
    while(it != q.end()){
        os << *it;
        it++;
    }
    return os;
}

class Point{
    public:
        int x;
        int y;
        Point(){}
        Point(int x_, int y_): x(x_), y(y_){}
        friend Point operator+(Point &left, Point &right){
            return Point(left.x + right.x, left.y + right.y);
        }
        bool in_boarder(){
            return (x >= 0 && x < p && y >= 0 && y < q);
        }
};

Point directions[8];

bool check(){
    bool ret = true;
    for (int i = 0; i < p; i++){
        for (int j = 0; j < q; j++){
            ret &= chess[i][j];
            if (!ret) return false;
        }
    }
    return ret;
}

void print_chess(){
    for (int i = 0; i < p; i++){
        for (int j = 0; j < q; j++){
            cout << chess[i][j] << " ";
        }
        cout << endl;
    }
}

bool dfs(int num, int let){
    chess[num][let] = 1;
    // push current location into stack
    string loc;
    loc.push_back('A' + let);
    loc.push_back('1' + num);
    ans.push_back(loc);

    // print chess as well as loc
    // cout << "----chess-----(ans=" << ans << ", num="<< num <<" let=" << let<<")" << endl;
    // print_chess();
    // cout << "--------------" << endl;

    // if the knight can jump to every location, return true
    if(check()){
        return true;
    }

    // if all eight sides are painted, return false
    bool end = true;
    Point pt(num, let);
    for (int i = 0; i < 8; i++){
        Point next_step = pt + directions[i];
        if (next_step.in_boarder())
            end &= chess[next_step.x][next_step.y];
    }
    if (end) {
        ans.pop_back();
        chess[num][let] = 0; // [bugfix] should pop the location and set it to 0
        return false;
    }

    // search by direction
    for (int i = 0; i < 8; i++){
        Point next_step = pt + directions[i];
        // each square should only be visited once
        if (chess[next_step.x][next_step.y])
            continue;
        // the next step should be in the boarder
        if (!next_step.in_boarder())
            continue;
        if (dfs(next_step.x, next_step.y)){
            return true;
        }
    }

    ans.pop_back();
    chess[num][let] = 0; // [bugfix] should pop the location and set it to 0
    return false;
}

/*
* A1 A2 ... An
* B1 B2 ... Bn
* ...
* N1 N2 ... Nn
*/

int main(){
    int n;
    cin >> n;
    directions[0] = Point(-1, -2);
    directions[1] = Point(1, -2);
    directions[2] = Point(-2, -1);
    directions[3] = Point(2, -1);
    directions[4] = Point(-2, 1);
    directions[5] = Point(2, 1);
    directions[6] = Point(-1, 2);
    directions[7] = Point(1, 2);
    for (int n_ = 0; n_ < n; n_++){
        cin >> p >> q;
        // ans = stack<string>();
        ans = deque<string>();
        // int chess[MAXN][MAXN];
        memset(chess, 0, sizeof(chess));
        cout << "Scenario #" << n_+1 << ":" << endl;
        if (!dfs(0, 0)){
            cout << "impossible" << endl << endl;
        }
        else{
            while(!ans.empty()){
                // cout << ans.top();
                cout << ans.front();
                // pop the first element of ans
                ans.pop_front();
            }
            cout << endl << endl;
        }
    }
    return 0;
}