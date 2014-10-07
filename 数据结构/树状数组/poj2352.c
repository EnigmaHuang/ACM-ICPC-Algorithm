#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxN 15005
#define MaxT 32005

int n,tree[MaxT],level[MaxN];

void add(int x,int value)
{
    int i;
    for (i=x;i<=MaxT;i+=lowbit(i)) tree[i]+=value;
}

int sum(int x)
{
    int res=0,i;
    for (i=x;i;i-=lowbit(i)) res+=tree[i];
    return res;
}

int main()
{
    int i,x,y;
    freopen("poj2352.txt","r",stdin);
    freopen("poj2352ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        memset(tree,0,sizeof(tree));
        memset(level,0,sizeof(level));
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            x++;
            level[sum(x)]++;   
            add(x,1);
        }
        for (i=0;i<n;i++) printf("%d\n",level[i]);
    }
    return 0;
}
