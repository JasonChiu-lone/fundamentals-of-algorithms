#include <stdio.h>
#include <string.h>
/********************************
思路类似于计数排序，不过不将第二个集合的互补元素个数加起来就好。
思路类似于计数排序，不过不将第二个集合的互补元素个数加起来就好。
*********************************/
int n,s,a,b;
int count,sum[10001],num;
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        memset(sum,0,sizeof(sum));
        scanf("%d",&s);
        num = 0;
        scanf("%d",&a);
        while(a--)
        {
            scanf("%d",&count);
            sum[count]++;
        }
        scanf("%d",&b);
        while(b--)
        {
            scanf("%d",&count);
            s>=count ? num += sum[s-count]:0;
        }
        printf("%d\n",num);
    }
    return 0;
}