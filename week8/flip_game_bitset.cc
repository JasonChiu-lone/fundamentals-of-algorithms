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
#include <bitset>
using namespace std;

bool board[4][4];

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

void flip(int i, int j){
    board[i][j] ^= 1;
    if (i > 0) board[i-1][j] ^= 1;
    if (i < 3) board[i+1][j] ^= 1;
    if (j > 0) board[i][j-1] ^= 1;
    if (j < 3) board[i][j+1] ^= 1;
}

template<size_t _Size>
ostream &operator<< (ostream &os, bitset<_Size> &b){
    for (int d = 0; d < _Size; d++)
        cout << b.test(d) << ' ';
    return os;
}

set<int> ans;

void print_board(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    char c;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            cin >> c;
            board[i][j] = (c=='b'?1:0);
        }
    }
    bitset<16> b;
    while(true){
        /*
        if (b.count() == 1){
            cout << b << endl;
        }
        */
        for (int d = 0; d < 16; d++){
            if (!b.test(d)) continue;
            flip(d / 4, d % 4);
        }
        /*
        if (b.count() == 1){
            cout << "flipped board = " << endl;
            print_board();
        }
        */
        if (check()){
            // cout << "found solution with step=" << b.count() << endl;
            ans.insert(b.count());
        }
        for (int d = 0; d < 16; d++){
            if (!b.test(d)) continue;
            flip(d / 4, d % 4);
        }
        if (b.all()) break;
        b = bitset<16>(b.to_ullong()+1);
    }
    if (ans.size())
        cout << *ans.begin() << endl;
    else
        cout << "Impossible" << endl;
    return 0;
}