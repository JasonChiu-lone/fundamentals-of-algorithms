#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int mark[1000010];
int ans[6];
long long int numA,numB;

void dfs(int *list,string obj,int size,int now,int before,int num){
    list[now]=num;
    long long int sum=0,temp=obj[0]-'0';
    for (int i = 1; i < size; ++i) {
        if(list[i]==list[i-1]){
            temp*=10;
            temp+=obj[i]-'0';
        }else{
            sum+=temp;
            temp=obj[i]-'0';
        }
        if(i==size-1)sum+=temp;
    }
    if(sum<=numA&&sum>=numB){
        numB = sum;
        mark[numB]++;
        memcpy(ans,list, sizeof(ans));
    }
    if(now!=size-1)dfs(list,obj,size,size-1,now,num+1);
    if(now!=before+1)dfs(list,obj,size,now-1,before,num);
    list[now]=num-1;
    if(before == 0&&now==size-1){
        sum=0,temp=obj[0]-'0';
        for (int i = 1; i < size; ++i) {
            if(list[i]==list[i-1]){
                temp*=10;
                temp+=obj[i]-'0';
            }else{
                sum+=temp;
                temp=obj[i]-'0';
            }
            if(i==size-1)sum+=temp;
        }
        if(sum<=numA&&sum>=numB){
            numB = sum;
            mark[numB]++;
            memcpy(ans,list, sizeof(ans));
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    string a,b;
    while(cin>>a>>b,a!="0"&&b!="0"){
        if(a==b||a.length()>b.length())cout<<b<<" "<<b<<endl;
        else if(a.length()<=b.length()){
            numA=0,numB=0;
            for (int i = 0; i < a.length(); ++i) {
                numA*=10;
                numA+=a[i]-'0';
            }
            for (int j = 0; j < b.length(); ++j) {
                numB+=b[j]-'0';
            }
            if(numA<numB){
                cout<<"error"<<endl;
                continue;
            }
            if(b.size()==1){
                cout<<b<<" "<<b<<endl;
                continue;
            }
            int list[6];
            for (int k = 0; k < 6; ++k) {
                list[k]=1;
            }
            numB=1;
            memset(mark,0, sizeof(mark));
            dfs(list,b,b.length(),b.length()-1,0,2);
            if(mark[numB]!=1)cout<<"rejected"<<endl;
            else{
                cout<<numB<<' '<<b[0];
                for (int i = 1; i < b.size(); ++i) {
                    if(ans[i]!=ans[i-1])cout<<' ';
                    cout<<b[i];
                }
                cout<<' '<<endl;
            }
        }
    }
    return 0;
}
