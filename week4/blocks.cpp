// [来源：POJ1390](http://bailian.openjudge.cn/practice/1390/)
// [解析](https://blog.csdn.net/abc15766228491/article/details/79725409)
/*
输入
The first line contains the number of tests t(1<=t<=15). Each case contains two lines. The first line contains an integer n(1<=n<=200), the number of boxes. The second line contains n integers, representing the colors of each box. The integers are in the range 1~n.
输出
For each test case, print the case number and the highest possible score.
样例输入

2
9
1 2 2 2 2 3 3 3 1
1
1
1
2
3
4
5
样例输出

Case 1: 29
Case 2: 1
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

#define MAXN 205

struct Block{
    int color;
    int size;
};

Block segment[MAXN];
int dp[MAXN][MAXN][MAXN];
/*
    * dp(l, r, len)的意思是，
    * 在条件 “区间[l, r]里并且后面有连续len个盒子和在r位置的盒子同颜色的盒子” 下，
    * 得到最高的分数是多少。
    * 注意，这里的条件是说，r后面有连续len个盒子和它同颜色，因为，在中间的不同颜色的盒子已经被消去了。
*/

int f(int start, int end, int extlen){
    if (dp[start][end][extlen])
        return dp[start][end][extlen];

    int score;

    // 方案一：把end和extlen一起消掉
    score = (segment[end].size + extlen) * (segment[end].size + extlen);
    
    if (start == end){
        dp[start][end][extlen] = score;
        return score;
    }
    else {
        score += f(start, end - 1, 0);
    }

    // 方案二：把end和前面的一起消掉
    for (int r = end - 1; r >= start; r--){
        if (segment[r].color == segment[end].color){
            score = max(score, f(start, r, segment[end].size + extlen) + f(r + 1, end - 1, 0));
        }
    }

    dp[start][end][extlen] = score;
    return score;
}

int main(){
    int t;
    cin >> t;
    for (int t_ = 0; t_ < t; t_++){
        int n;
        cin >> n;
        int blocks[MAXN];
        memset(blocks, 0, sizeof(blocks));
        for (int n_ = 0; n_ < n; n_++)
            cin >> blocks[n_];
        memset(dp, 0, sizeof(dp));

        int n_segment = 0;
        int current_color = blocks[0];
        int current_size = 0;

        for (int i = 0; i < n; i++){
            if (blocks[i] != current_color){
                segment[n_segment].color = current_color;
                segment[n_segment].size = current_size;
                current_color = blocks[i];
                current_size = 1;
                n_segment ++;
                continue;
            }
            else{
                current_size += 1;
            }
        }
        segment[n_segment].color = current_color;
        segment[n_segment].size = current_size;

        cout << "Case " << t_+1 << ": " << f(0, n_segment, 0) << endl;
    }
    return 0;
}