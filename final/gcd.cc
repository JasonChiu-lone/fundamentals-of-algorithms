#include <iostream>
using namespace std;

int gcd(int m, int n) {
    if (n == 0) { return m; }
    return gcd(n, m % n);
}

int main() {
//  freopen("in.txt", "r", stdin);
    int m, n;
    while(cin >> m >> n) {
        cout << gcd(m, n) << endl;
    }
    return 0;
}