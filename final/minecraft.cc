#include <iostream>
#include <utility>
using namespace std;

int main(){
    int C, N;
    cin >> C;
    while(C--){
        cin >> N;
        int ans = 0x7fffffff;
        for (int i = N; i >= 1; i--){
            for (int j = N / i; j >= 1; j--){
                if (N % (i * j) == 0){
                    int k = N / i / j;
                    ans = min(ans, 2*(i*j+j*k+i*k));
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}