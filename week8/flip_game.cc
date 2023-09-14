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

#define MAXN (1<<17)

bool board[4][4];
class Point{
    public:
        int x;
        int y;
        Point(int x_, int y_): x(x_), y(y_){}
        friend bool operator==(Point &left, Point &right){
            return left.x==right.x && left.y==right.y;
        }
};
queue<vector<Point> > q; // coordinate of point to be flipped

void flip(vector<Point> &v){
    vector<Point>::iterator it = v.begin();
    while (it != v.end()){
                       board[it->x][it->y]   ^= true;
        if (it->x > 0) board[it->x-1][it->y] ^= true;
        if (it->x < 3) board[it->x+1][it->y] ^= true;
        if (it->y > 0) board[it->x][it->y-1] ^= true;
        if (it->y < 3) board[it->x][it->y+1] ^= true;
        it++;
    }
}

bool check(){
    int r = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            r += board[i][j];
        }
    }
    if (r == 0 || r == 16)
        return true;
    else return false;
}

bool contain(vector<Point> &v, Point p){
    for (vector<Point>::iterator it = v.begin(); it != v.end(); it++){
        if (*it == p)
            return true;
    }
    return false;
}

void print_vector(vector<Point> &v){
    for (vector<Point>::iterator it = v.begin(); it != v.end(); it++){
        cout << "(" << it->x << "," <<  it->y << ") ";
    }
    cout << endl;
}

void bfs(){
    int n_trial = 0;
    while (n_trial++ < MAXN+1){
        int qsize = q.size();
        for (int s = 0; s < qsize; s++){
            // print_vector(q.front());
            flip(q.front());
            if (check()){
                cout << q.front().size() << endl;
                return;
            }
            else{
                flip(q.front());
                for (int i = 0; i < 4; i++){
                    for (int j = 0; j < 4; j++){
                        if (!contain(q.front(), Point(i, j))){ // if Point(i, j) not in q.front()
                            vector<Point> next_trial = q.front();
                            next_trial.push_back(Point(i, j));
                            q.push(next_trial);
                        }
                    }
                }
                q.pop();
            }
        }
    }
    cout << "Impossible" << endl;
    return;
    // there are q.size() points in the queue to be flipped
    // for each, flip it. and if the board is not purely black or white, pop it, and push each combination into the queue
}



int main(){
    char c;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            cin >> c;
            board[i][j] = c=='b'?1:0;
            q.push(vector<Point>(1, Point(i, j)));
        }
    }
    bfs();
    return 0;
}