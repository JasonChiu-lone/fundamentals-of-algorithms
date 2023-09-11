//Garbage bomb
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
 
#define MAX 1025
 
int map[MAX][MAX];    //枚举地图各点可清除垃圾数
 
/*垃圾点*/
struct Point{
    int x, y;    //坐标
    int m;    //垃圾数
}p[21];
 
int main()
{
    int T;
    cin >> T;
    while(T--){
        memset(map, 0, sizeof(map));
        int d, n;
        scanf("%d%d", &d, &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].m);
 
        int ans = 0, np = 0;
        for (int i = 0; i < n; i++)
        {
            for (int row = p[i].x - d; row <= p[i].x + d; row++)
                if (row >= 0 && row < MAX){
                for (int col = p[i].y - d; col <= p[i].y + d; col++)
                {
                    if (col >= 0 && col < MAX)
                    {
                        map[row][col] += p[i].m;
                        /*refresh*/
                        if (ans < map[row][col])
                        {
                            ans = map[row][col];
                            np = 1;
                        }
                        else if (ans == map[row][col]) np++;
                    }
                }
                }
        }
        printf("%d %d\n", np, ans);
    }
    return 0;
}