#include <stdio.h>

int main()
{
    int n,m,p,temp,i;
    freopen("poj2085.txt","r",stdin);
    freopen("poj2085ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m) && n>0)
    {
        for (p=1;(p*(p-1))/2<m;p++);
        temp=(p*(p-1))/2;
        for (i=1;i<=n-p;i++) printf("%d ",i);
        printf("%d ",n-temp+m);
        for (i=n;i>=n-p+1;i--) if (i!=n-temp+m) printf("%d ",i);
        printf("\n");
    }
    return 0;
}
