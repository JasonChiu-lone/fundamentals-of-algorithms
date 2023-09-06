/*** 
 * @Author: Jason Chiu uranuslight@outlook.com
 * @Date: 2023-09-06 21:30:22
 * @LastEditors: Jason Chiu uranuslight@outlook.com
 * @LastEditTime: 2023-09-06 22:59:22
 * @FilePath: /cppProjects/fundamentals-of-algorithms/week6/knight.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
#include <stack>
using namespace std;

#define MAXN 26
int p, q; // p numbers; q letters
int chess[MAXN][MAXN];
stack<string> ans;

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
    cout << "----chess-----" << endl;
    print_chess();
    cout << "--------------" << endl;
    if(check()){
        // cout << (char) ('A' + let) << (char) ('1' + num);
        string loc;
        loc.push_back('A' + let);
        loc.push_back('1' + num);
        ans.push(loc);
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
    if (end) return false;

    // search by direction
    for (int i = 0; i < 8; i++){
        Point next_step = pt + directions[i];
        if (chess[next_step.x][next_step.y]) continue;
        if (!next_step.in_boarder()) continue;
        if (dfs(next_step.x, next_step.y)){
            string loc;
            loc.push_back('A' + let);
            loc.push_back('1' + num);
            ans.push(loc);
            return true;
        }
    }
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
        ans = stack<string>();
        // int chess[MAXN][MAXN];
        memset(chess, 0, sizeof(chess));
        cout << "Scenario #" << n_+1 << ":" << endl;
        if (!dfs(0, 0)){
            cout << "impossible" << endl << endl;
        }
        else{
            while(!ans.empty()){
                cout << ans.top();
                ans.pop();
            }
            cout << endl << endl;
        }
    }
    return 0;
}