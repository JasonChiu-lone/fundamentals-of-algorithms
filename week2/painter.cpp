/*
2813:画家问题  http://bailian.openjudge.cn/practice/2813/
总时间限制: 1000ms 内存限制: 65536kB
描述
有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。Bob是个画家，想把全部的砖都涂成黄色。但他的画笔不好使。当他用画笔涂画第(i, j)个位置的砖时， 位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)上的砖都会改变颜色。请你帮助Bob计算出最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色。

![](http://media.openjudge.cn/images/2813_1.jpg)

输入
第一行是一个整数n (1≤n ≤15)，表示墙的大小。接下来的n行表示墙的初始状态。每一行包含n个字符。第i行的第j个字符表示位于位置(i,j)上的砖的颜色。“w”表示白砖，“y”表示黄砖。
输出
一行，如果Bob能够将所有的砖都涂成黄色，则输出最少需要涂画的砖数，否则输出“inf”。
样例输入
5
wwwww
wwwww
wwwww
wwwww
wwwww
样例输出
15 
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

bool wall[15][15];
int n;

class Binary{
    public:
        bool bits[15];
        Binary(){
            memset(bits, 0, sizeof(bits));
        }
        void operator ++ (){
            bool carry = 1;
            for (int b = 0; b < 15; b++){
                bits[b] ^= carry;
                carry ^= bits[b];
                if (!carry) break;
            }
        }
        bool operator < (int right){
            for (int b = 14; b >= 0; b--){
                if (bits[b]){
                    if (b < right - 1){
                        return true;
                    }
                    else return false;
                }
            }
            return false;
        }
        friend ostream &operator<< (ostream &os, Binary b){
            for (int i = 0; i < n; i ++){
                cout << b.bits[i] << " ";
            }
            return os;
        }
};

void paint(bool wall_[15][15], int i, int j){
    if (i >= n || j >= n) return;
    // *********** change (i, j) ***********
    wall_[i][j] ^= 1;
    // change (i-1, j)
    if (i >= 1) wall_[i-1][j] ^= 1;
    // change (i+1, j)
    if (i < n-1) wall_[i+1][j] ^= 1;
    // change (i, j-1)
    if (j >= 1) wall_[i][j-1] ^= 1;
    // change (i, j+1)
    if (j < n-1) wall_[i][j+1] ^= 1;
}

void print(bool wall_[15][15]){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << wall_[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------" << endl;
}

int main(){
    int ans = 0x7fffffff;
    cin >> n;
    char tmp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> tmp;
            wall[i][j] = (tmp == 'y');
        }
    }
    // 首先枚举第一行是否paint
    Binary bin;
    for (int iter = 0; iter < 1 << n; ++bin, iter++){
        // cout << "iter=" << iter << "\t" << bin << endl;
        // 记录paint次数
        int n_paint = 0;
        // bin是枚举的第一行
        bool wall_[15][15];
        memcpy(wall_, wall, sizeof(wall));
        for (int j = 0; j < n; j++){
            if (bin.bits[j]){
                paint(wall_, 0, j);
                n_paint++;
            }
        }
        // 然后根据第一行paint后的结果，paint至最后一行
        for (int i = 1; i < n; i++){
            for (int j = 0; j < n; j++){
                if (!wall_[i-1][j]){
                    paint(wall_, i, j);
                    n_paint++;
                }
            }
            // print(wall_);
        }
        // 判断最后一行是否全为1
        bool full = true;
        for (int j = 0; j < n; j++)
            full &= wall_[n-1][j];
        if (full) ans = min(ans, n_paint);
    }
    if (ans < 0x7fffffff) cout << ans << endl;
    else cout << "inf" << endl;

    return 0;
}