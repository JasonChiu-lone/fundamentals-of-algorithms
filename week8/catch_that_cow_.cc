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

void print_set(set<int> &s){
    for (set<int>::iterator it = s.begin(); it != s.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
}

int main(){
    int N, K;
    cin >> N >> K;
    vector<set<int> > accessible;
    accessible.push_back(set<int>());
    accessible.rbegin()->insert(N);
    // cout << accessible[0][0] << endl;
    while (find(accessible.rbegin()->begin(), accessible.rbegin()->end(), K) == accessible.rbegin()->end()){
        set<int> new_accessible;
        for(set<int>::iterator it = accessible.rbegin()->begin(); it !=accessible.rbegin()->end(); it++){
            if (*it > 0) new_accessible.insert(*it-1);
            new_accessible.insert(*it+1);
            new_accessible.insert(*it*2);
        }
        cout << "Accessible with steps of " << accessible.size()-1 << ":" << endl;
        print_set(new_accessible);
        accessible.push_back(new_accessible);
    }
    cout << accessible.size()-1 << endl;
    return 0;
}