#include<stdio.h>
#define MaxN 200001

int a[MaxN];

int main()
{
    int n,ans,s,i;
    freopen("hdoj2176.txt","r",stdin);
    freopen("hdoj2176ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            ans=ans^a[i];
        }
        if (ans==0) printf("No\n");
        else
        {
           printf("Yes\n");
           for (i=0;i<n;i++)
           {
               s=ans^a[i];
               if (s<a[i]) printf("%d %d\n",a[i],s);
           }
        }
    }
   return 0;
}
