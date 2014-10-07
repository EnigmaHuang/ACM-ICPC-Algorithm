#include<stdio.h>

int main()
{
    int t,a,n,i,sum1,sum2,ans;
    freopen("hdoj2509.txt","r",stdin);
    freopen("hdoj2509ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        sum1=sum2=ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&a);
            if (a>=2) sum1++; else sum2++;
            ans^=a;
        }
        //最开始局势为S2,则先下的人一定会先夺得局势S1
        if ((ans!=0 && sum1!=0) || (ans==0 && sum1==0)) printf("Yes\n");
        else if ((ans==0 && sum1>=2) || (ans!=0 && sum2%2!=0 && sum1==0)) printf("No\n");
    }
    return 0;
}

