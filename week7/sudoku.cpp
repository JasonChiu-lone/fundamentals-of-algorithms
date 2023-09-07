// POJ2982

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

int s[9][9];
bool r[10][10];
bool c[10][10];
bool b[10][10];

bool check(){
    bool ret = true;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            ret &= (s[i][j] > 0);
    return ret;
}

int block(int r_, int c_){
    if (0 <= r_ && r_ < 3 && 0 <= c_ && c_ < 3) return 0;
    if (0 <= r_ && r_ < 3 && 3 <= c_ && c_ < 6) return 1;
    if (0 <= r_ && r_ < 3 && 6 <= c_ && c_ < 9) return 2;
    if (3 <= r_ && r_ < 6 && 0 <= c_ && c_ < 3) return 3;
    if (3 <= r_ && r_ < 6 && 3 <= c_ && c_ < 6) return 4;
    if (3 <= r_ && r_ < 6 && 6 <= c_ && c_ < 9) return 5;
    if (6 <= r_ && r_ < 9 && 0 <= c_ && c_ < 3) return 6;
    if (6 <= r_ && r_ < 9 && 3 <= c_ && c_ < 6) return 7;
    if (6 <= r_ && r_ < 9 && 6 <= c_ && c_ < 9) return 8;
}

void print_chess(){
    cout << "------------sudoku-----------" << endl;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
            cout << s[i][j] << " ";
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}

bool solve(int i_, int j_){
    // print_chess();
    if (check()) return true;
    // cout << "solving i_=" << i_ <<" j_=" << j_ << endl;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (s[i][j])
                continue;
            for (int n = 1; n <= 9; n++){
                if (r[i][n] || c[j][n] || b[block(i, j)][n])
                    continue;

                if (i == 8 && j == 8){
                    s[i][j] = n;
                    return true; // problem solved
                }

                s[i][j] = n;
                r[i][n] = true;
                c[j][n] = true;
                b[block(i, j)][n] = true;

                if (solve(i, j)) return true;

                s[i][j] = 0;
                r[i][n] = false;
                c[j][n] = false;
                b[block(i, j)][n] = false;
            }
            if (s[i][j] == 0) return false;
        }
    }
    return false;
}



int main(){
    int n;
    cin >> n;
    while (n--){
        memset(s, 0, sizeof(s));
        memset(r, 0, sizeof(r));
        memset(c, 0, sizeof(c));
        memset(b, 0, sizeof(b));
        for (int i = 0; i < 9; i++){
            getchar();
            for (int j = 0; j < 9; j++){
                s[i][j] = getchar() - '0';
                r[i][s[i][j]] = s[i][j] > 0;
                c[j][s[i][j]] = s[i][j] > 0;
                b[block(i, j)][s[i][j]] = s[i][j] > 0;
            }
        }
        solve(0, 0);
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                cout << s[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}