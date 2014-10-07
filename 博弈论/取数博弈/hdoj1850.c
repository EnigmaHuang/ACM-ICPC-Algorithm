#include<stdio.h>
#define MaxN 1000001

int a[MaxN];

int main()
{
    int n,ans,s,i,cnt;
    freopen("hdoj1850.txt","r",stdin);
    freopen("hdoj1850ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        cnt=ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            ans=ans^a[i];
        }
        for (i=0;i<n;i++)
        {
           s=ans^a[i];
           if (s<a[i]) cnt++;
        }
        printf("%d\n",cnt);
    }
   return 0;
}
