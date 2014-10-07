#include<stdio.h>
#define MaxN 200001

int a[MaxN];

int main()
{
    int n,ans,s,i,num;
    freopen("poj2975.txt","r",stdin);
    freopen("poj2975ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            ans=ans^a[i];
        }
        num=0;
        if (ans)
        {
           for (i=0;i<n;i++)
           {
               s=ans^a[i];
               if (s<a[i]) num++;
           }
        }
        printf("%d\n",num);
    }
   return 0;
}
