#include <stdio.h>
#include <string.h>

#define MaxN 501

int a[MaxN][MaxN],b[MaxN][MaxN],c[MaxN][MaxN];

int main()
{
    int i,j,k,n,flag;
    freopen("poj3318.txt","r",stdin);
    freopen("poj3318ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++)
            for (j=0;j<n;j++) scanf("%d",&a[i][j]);
        for (i=0;i<n;i++)
            for (j=0;j<n;j++) scanf("%d",&b[i][j]);
        for (i=0;i<n;i++)
            for (j=0;j<n;j++) scanf("%d",&c[i][j]);
        for (i=0;i<n;i++)
            for (j=0;j<n;j++) if (a[i][j])
                for (k=0;k<n;k++)
                    c[i][k]-=a[i][j]*b[j][k];
        flag=1;
        for (i=0;i<n;i++)
            for (j=0;j<n;j++) if (c[i][j]!=0)
            {
                flag=0;
                i=j=n;  //一层break不行，直接跳到终止条件 
            }
        if (flag) puts("YES"); else puts("NO");
    }
} 
