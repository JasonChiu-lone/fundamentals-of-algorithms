#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

#define MAXN 200
int map[MAXN][MAXN];
int ans;
int R, C;

struct Point{
    int x, y;
    Point(int x, int y): x(x), y(y){}
    Point operator+(Point &p){
        return Point(x + p.x, y + p.y);
    }
};
Point D[4] = {Point(-1, 0), Point(1, 0), Point(0, 1), Point(0, -1)};

void bfs(int sx, int sy){
    queue<Point> q;
    q.push(Point(sx, sy));
    while(q.size()){
        Point pt = q.front();
        q.pop();
        for (int d = 0; d < 4; d++){
            Point next_pt = pt + D[d];
            if (!(next_pt.x >= 0 && next_pt.x < R && next_pt.y >= 0 && next_pt.y < C)) continue; // 边界
            if (map[next_pt.x][next_pt.y] == -2){
                ans = map[pt.x][pt.y] + 1;
                return;
            }
            if (map[next_pt.x][next_pt.y] == 0){
                map[next_pt.x][next_pt.y] = map[pt.x][pt.y] + 1;
                q.push(next_pt);
            }
        }
    }
    // no answer
}

int main(){
    int T;
    cin >> T;
    while(T--){
        
        int sx, sy;
        cin >> R >> C;
        ans = 0x7fffffff;
        memset(map, -1, sizeof(map));
        char c;
        for (int i = 0; i < R; i++){
            for (int j = 0; j < C; j++){
                cin >> c;
                if (c == 'S'){
                    map[i][j] = 0;
                    sx = i;
                    sy = j;
                }
                else if (c == 'E'){
                    map[i][j] = -2;
                }
                else if (c == '#'){
                    map[i][j] = -1;
                }
                else if (c == '.'){
                    map[i][j] = 0;
                }
            }
        }
        bfs(sx, sy);
        if (ans < 0x7fffffff) cout << ans << endl;
        else cout << "oop!" << endl;
    }
    return 0;
}