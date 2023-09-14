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

int laby[5][5];

class Point{
    public:
        int x;
        int y;
        Point(int x_, int y_): x(x_), y(y_){}
};

queue<Point> q;

void bfs(){
    while(q.size()){
        Point current = q.front();
        q.pop();
        if (current.x > 0 && laby[current.x-1][current.y] == 0){
            laby[current.x-1][current.y] = laby[current.x][current.y] + 1;
            q.push(Point(current.x-1, current.y));
        }
        if (current.x < 4 && laby[current.x+1][current.y] == 0){
            laby[current.x+1][current.y] = laby[current.x][current.y] + 1;
            q.push(Point(current.x+1, current.y));
        }
        if (current.y > 0 && laby[current.x][current.y-1] == 0){
            laby[current.x][current.y-1] = laby[current.x][current.y] + 1;
            q.push(Point(current.x, current.y-1));
        }
        if (current.y < 4 && laby[current.x][current.y+1] == 0){
            laby[current.x][current.y+1] = laby[current.x][current.y] + 1;
            q.push(Point(current.x, current.y+1));
        }
    }
}

void print_path(int x, int y, int s){
    if (s == 1){
        cout << "(" << x << ", " << y << ")" << endl;
        return;
    }
    if (x > 0 && laby[x-1][y] == s-1){
        print_path(x-1, y, s-1);
    }
    else if (x < 4 && laby[x+1][y] == s-1){
        print_path(x+1, y, s-1);
    }
    else if (y > 0 && laby[x][y-1] == s-1){
        print_path(x, y-1, s-1);
    }
    else if (y < 4 && laby[x][y+1] == s-1){
        print_path(x, y+1, s-1);
    }
    cout << "(" << x << ", " << y << ")" << endl;
    return;
}

int main(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            cin >> laby[i][j];
            if (laby[i][j])
                laby[i][j] = -1;
        }
    }
    laby[0][0] = 1;
    q.push(Point(0, 0));
    bfs();
    print_path(4, 4, laby[4][4]);
    return 0;
}