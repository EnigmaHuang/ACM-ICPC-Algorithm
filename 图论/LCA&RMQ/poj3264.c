#include <stdio.h>

#define MaxN 50005
#define MaxL 19
#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)

int min[MaxN][MaxL],max[MaxN][MaxL];

void MakeRMQ(int n)
{
    int i,j;
    for (j=1;(1<<j)<=n;j++)
        for (i=1;i+(1<<j)-1<=n;i++)
        {
            min[i][j] = Min(min[i][j-1],min[i+(1<<(j-1))][j-1]);
            max[i][j] = Max(max[i][j-1],max[i+(1<<(j-1))][j-1]);
        }

}

int RMQ(int left,int right)
{
    int k=0,res;
    while ( (1<<(k+1)) <= right-left+1 ) k++;
    res=Max(max[left][k],max[right-(1<<k)+1][k]);
    res-=Min(min[left][k],min[right-(1<<k)+1][k]);
    return res;
}

int main()
{
    int n,m,a,b,w,i;
    freopen("poj3264.txt","r",stdin);
    freopen("poj3264ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++)
        {
            scanf("%d",&w);
            max[i][0]=min[i][0]=w;
        }
        MakeRMQ(n);
        while (m--)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",RMQ(a,b));
        }
    }
    return 0;
}
