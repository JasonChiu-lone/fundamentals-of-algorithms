// http://bailian.openjudge.cn/practice/1458

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

#define MAXL 2010

int lcs(char left[201], char right[201]){
    int len_left, len_right;
    for (int i = 0; i < 201; i++){
        if (left[i] == '\0'){
            len_left = i;
            break;
        }
    }
    for (int i = 0; i < 201; i++){
        if (right[i] == '\0'){
            len_right = i;
            break;
        }
    }
    int pd[201][201];
    memset(pd, 0, sizeof(pd));
    for (int i = 0; i < len_left; i++){
        for (int j = 0; j < len_right; j++){
            if (left[i] == right[j]){
                pd[i][j] = (i>0&&j>0)? pd[i-1][j-1] + 1: 1;
            }
            else{
                // pd[i][j] = (i>0&&j>0)? max(pd[i][j-1], pd[i-1][j]): 0;
                if (i == 0 && j == 0){
                    pd[i][j] = 0;
                }
                else if (i == 0){
                    pd[i][j] = pd[i][j-1];
                }
                else if (j == 0){
                    pd[i][j] = pd[i-1][j];
                }
                else{
                    pd[i][j] = max(pd[i][j-1], pd[i-1][j]);
                }
            }
        }
    }
    return pd[len_left-1][len_right-1];
}

int main(){
    char left[201];
    char right[201];
    while (cin >> left){
        cin >> right;
        cout << lcs(left, right) << endl;
    }
    return 0;
}