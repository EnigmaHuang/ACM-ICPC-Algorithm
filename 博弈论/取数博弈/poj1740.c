#include<stdio.h>
#include<string.h>

int cnt[105];

int main()
{
    int n,i,x;
    freopen("poj1740.txt","r",stdin);
    freopen("poj1740ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        memset(cnt,0,sizeof(cnt));
        for (i=0;i<n;i++)
        {
            scanf("%d",&x);
            cnt[x]++;
        }
        for (i=1;i<=100;i++) if (cnt[i] & 1) break;
        printf("%d\n",i!=101);
    }
    return 0;
}
