//什么是记忆化搜索？
//简单的说就是据的值保存下来，比这个数值小或者大的时间我们就没有必要再继续访问。
 
#include<iostream>
using namespace std;
int to[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m;
int high[105][105];
int maxLen[105][105];
bool check(int x, int y){
	if(x >= 1 && y >= 1 && x <= n && y <= m)
		return 1;
	else
		return 0;
}
 
int dfs(int x, int y){
	if (maxLen[x][y] != 0)	//退出边界 ，这个点已经搜索过，或者这个点是边界
		return maxLen[x][y];
	
	maxLen[x][y] = 1;        //最低的点就是1;
	for(int i = 0; i <= 4; i++){    //搜索上下左右
		int x1 = x + to[i][0];
		int y1 = y + to[i][1];
		if( check(x1, y1) && high[x1][y1] < high[x][y]){    //判断能否向下滑
			maxLen[x][y] = max(dfs(x1, y1) + 1, maxLen[x][y]);
		}
	}
	return maxLen[x][y];    //返回搜索过的点，并保存在数组中
}
int main(){
 
	cin >> n >> m;
 
	int ans = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> high[i][j];
			maxLen[i][j] = 0;      
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ans = max(ans, dfs(i, j));	//搜索每一个点，并且找出最大值
		}
	}
	cout << ans << endl;
	return 0;
} 