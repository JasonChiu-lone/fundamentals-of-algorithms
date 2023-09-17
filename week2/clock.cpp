#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

/**************************************************************************
 * 2814:拨钟问题 http://bailian.openjudge.cn/practice/2814/
 * 总时间限制: 1000ms 内存限制: 65536kB
描述
有9个时钟，排成一个3*3的矩阵。

|-------|    |-------|    |-------|
|       |    |       |    |   |   |
|---O   |    |---O   |    |   O   |
|       |    |       |    |       |
|-------|    |-------|    |-------|
    A            B            C    

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O   |    |   O   |
|   |   |    |   |   |    |   |   |
|-------|    |-------|    |-------|
    D            E            F    

|-------|    |-------|    |-------|
|       |    |       |    |       |
|   O   |    |   O---|    |   O   |
|   |   |    |       |    |   |   |
|-------|    |-------|    |-------|
    G            H            I    
(图 1)
现在需要用最少的移动，将9个时钟的指针都拨到12点的位置。共允许有9种不同的移动。如下表所示，每个移动会将若干个时钟的指针沿顺时针方向拨动90度。



移动    影响的时钟
 
 1         ABDE
 2         ABC
 3         BCEF
 4         ADG
 5         BDEFH
 6         CFI
 7         DEGH
 8         GHI
 9         EFHI    
输入
9个整数，表示各时钟指针的起始位置，相邻两个整数之间用单个空格隔开。其中，0=12点、1=3点、2=6点、3=9点。
输出
输出一个最短的移动序列，使得9个时钟的指针都指向12点。按照移动的序号从小到大输出结果。相邻两个整数之间用单个空格隔开。
样例输入
3 3 0 
2 2 2 
2 1 2 
样例输出
4 5 8 9 
**************************************************************************/

int angles[9];

class Move{
    public:
        short steps[9]; // 分别对应移动1-移动9的操作次数，step[i]取0-3
        Move(){
            for (int i = 0; i < 9; i++)
                steps[i] = 0;
        }
        void operator++(){
            bool carry = 1;
            for (int digit = 0; digit < 9; digit++){
                if (carry == 0) break;
                steps[digit] += carry;
                carry = steps[digit] > 3;
                steps[digit] %= 4;
            }
        }
};

bool test(Move &move){
    // copy angles
    int angles_[9];
    memcpy(angles_, angles, sizeof(angles));
    // carry out move.steps to angles_
    for (int d = 0; d < 9; d++){
        for (int m = 0; m < move.steps[d]; m++){
            switch(d){
            case 0:
                angles_[0]++;
                angles_[1]++;
                angles_[3]++;
                angles_[4]++;
                break;
            case 1:
                angles_[0]++;
                angles_[1]++;
                angles_[2]++;
                break;
            case 2:
                angles_[1]++;
                angles_[2]++;
                angles_[4]++;
                angles_[5]++;
                break;
            case 3:
                angles_[0]++;
                angles_[3]++;
                angles_[6]++;
                break;
            case 4:
                angles_[1]++;
                angles_[3]++;
                angles_[4]++;
                angles_[5]++;
                angles_[7]++;
                break;
            case 5:
                angles_[2]++;
                angles_[5]++;
                angles_[8]++;
                break;
            case 6:
                angles_[3]++;
                angles_[4]++;
                angles_[6]++;
                angles_[7]++;
                break;
            case 7:
                angles_[6]++;
                angles_[7]++;
                angles_[8]++;
                break;
            case 8:
                angles_[4]++;
                angles_[5]++;
                angles_[7]++;
                angles_[8]++;
                break;
            default:
                break;
            }
        }
        
    }
    for (int clock_ = 0; clock_ < 9; clock_++){
        if (angles_[clock_] % 4 != 0) return false;
    }
    return true;
}

int main(){
    for (int i = 0; i < 9; i++){
        cin >> angles[i];
    }
    Move move;
    while (true){
        if (test(move)){
            for (int c = 0; c < 9; c++){
                if (move.steps[c]){
                    for (int s = 0; s < move.steps[c]; s++){
                        cout << c + 1
                         << " ";
                    }
                }
            }
            break;
        }
        else{
            ++move;
        }
    }
    return 0;
}