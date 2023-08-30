/*
## 编程题＃1： 完美覆盖

[来源: POJ](http://cxsjsx.openjudge.cn/mooc2015test/f/) (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

**注意： 总时间限制: 1000ms 内存限制: 65536kB**

### 描述

一张普通的国际象棋棋盘，它被分成 8 乘 8 (8 行 8 列) 的 64 个方格。设有形状一样的多米诺牌，每张牌恰好覆盖棋盘上相邻的两个方格，即一张多米诺牌是一张 1 行 2 列或者 2 行 1 列的牌。那么，是否能够把 32 张多米诺牌摆放到棋盘上，使得任何两张多米诺牌均不重叠，每张多米诺牌覆盖两个方格，并且棋盘上所有的方格都被覆盖住？我们把这样一种排列称为棋盘被多米诺牌完美覆盖。这是一个简单的排列问题，同学们能够很快构造出许多不同的完美覆盖。但是，计算不同的完美覆盖的总数就不是一件容易的事情了。不过，同学们 发挥自己的聪明才智，还是有可能做到的。

现在我们通过计算机编程对 3 乘 n 棋盘的不同的完美覆盖的总数进行计算。

![img](https://d3c33hcgiwev3.cloudfront.net/nEQ6chlgEeW9xiIAC9pDjg_88db5e2d9603c4dddebde2dde3926a69_Screen-Shot-2015-06-22-at-9.30.23-PM.png?Expires=1519603200&Signature=DrBx-F~5zZntjPuvzZ~ZJoF0d03MQe8wbhnAovd99MphnYAtRr6pFmaipa1Opigj2DkYXnlSMPEbsUEHGU6onITkm7W0yfo47TAwzaxqQrDEnpw~hlmYOWdeDrChf10DWU-CrD~eURXRB3vBZA4HtZrLv3umpugEm5LWJ-ZYhpE_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A)

任务

对 3 乘 n 棋盘的不同的完美覆盖的总数进行计算。

### 输入

一次输入可能包含多行，每一行分别给出不同的 n 值 ( 即 3 乘 n 棋盘的列数 )。当输入 -1 的时候结束。

n 的值最大不超过 30.

### 输出

针对每一行的 n 值，输出 3 乘 n 棋盘的不同的完美覆盖的总数。

### 样例输入

```
2
8
12
-1
```

### 样例输出

```
3
153
2131
```
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
using namespace std;

int n;
int answers[30];

void print(bool board[5][32]){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j <= n + 1; j++){
            cout << (board[i][j]?'x':'o') << " ";
        }
        cout << endl;
    }
}

int is_left_rect(bool board[5][32]){
    int left_x = 0;
    for (int j = 1; j <= n; j++){
        if (board[1][j] == 0){
            left_x = j;
            break;
        }
    }
    if (left_x == 0) return false;
    bool ret = true;
    for (int i = 1; i < 4; i++){
        for (int j = 1; j <= n; j++){
            if (i < left_x) ret &= board[i][j];
            else ret ^= board[i][j];
            if (!ret) return false;
        }
    }
    return n - left_x + 1;
}

int solve(bool board[5][32], int last_i, int last_j, int ans){
    // cout << "last_i=" << last_i << " last_j=" << last_j << " solving:" << endl;
    // print(board);
    // shortcut
    int rect_width = is_left_rect(board);
    if (rect_width && answers[rect_width-1] != -1){
        cout << "this is helping" << endl;
        return answers[rect_width-1];
    }
    // 终止条件1：棋盘被填满
    bool full = true;
    for (int i = 1; i < 4; i++){
        for (int j = 1; j <= n; j++){
            full &= board[i][j];
        }
    }
    if (full){
        return 1;
    }
    // 从左到右，对于每个空缺，尝试在该处放置骨牌
    bool board_[5][32];
    int ret = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 32; j++)
            board_[i][j] = board[i][j];
    for (int j = last_j; j <= n; j++){
        int i = 1;
        if (j == last_j) i = last_i;
        for (; i < 4; i++){
            if (board[i][j] == 0){ // 棋盘在(i, j)处空白
                if (board[i+1][j] == 0){ // 可以竖着摆
                    board_[i][j] = 1;
                    board_[i+1][j] = 1;
                    ret += solve(board_, i, j, ans);
                    // recover board
                    board_[i][j] = 0;
                    board_[i+1][j] = 0;
                }
                if (board[i][j+1] == 0){ // 可以横着摆
                    board_[i][j] = 1;
                    board_[i][j+1] = 1;
                    ret += solve(board_, i, j, ans);
                    // recover board
                    board_[i][j] = 0;
                    board_[i][j+1] = 0;
                }
                
            }
        }
    }
    /*
    for (int i = last_i; i < 4; i++){
        int j = (i == last_i)?(last_j):1;
        for (; j <= n; j++){
            if (board[i][j] == 0){ // 棋盘在(i, j)处空白
                if (board[i][j+1] == 0){ // 可以横着摆
                    board_[i][j] = 1;
                    board_[i][j+1] = 1;
                    ret += solve(board_, i, j, ans);
                    // recover board
                    board_[i][j] = 0;
                    board_[i][j+1] = 0;
                }
                if (board[i+1][j] == 0){ // 可以竖着摆
                    board_[i][j] = 1;
                    board_[i+1][j] = 1;
                    ret += solve(board_, i, j, ans);
                    // recover board
                    board_[i][j] = 0;
                    board_[i+1][j] = 0;
                }
            }
        }
    }*/
    if(rect_width) answers[rect_width-1] = ret;
    return ans * ret;
}



int main(){
    memset(answers, -1, sizeof(answers));
    while(true){
        cin >> n;
        if (n == -1) break;
        if (n == 0){cout << 1 << endl; continue;}

        bool board[5][32];
        // 设立边界
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 32; j++){
                if (i == 0 || i == 4 || j == 0 || j > n){
                    board[i][j] = 1;
                }
                else board[i][j] = 0;
            }
        }

        answers[n-1] = solve(board, 1, 1, 1);
        cout << answers[n-1] << endl;
    }
    return 0;
}