#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxT 1030

int tree[MaxT][MaxT];

void add(int x,int y,int value)
{
    int i,j;
    for (i=x;i<=MaxT;i+=lowbit(i))
        for (j=y;j<=MaxT;j+=lowbit(j))
            tree[i][j]+=value;
}

int sum(int x,int y)
{
    int i,j,res=0;
    for (i=x;i;i-=lowbit(i))
        for (j=y;j;j-=lowbit(j))
            res+=tree[i][j];
    return res;
}

int main ()
{
    int n,op,x1,x2,y1,y2,a,ans;
    freopen("poj1195.txt","r",stdin);
    freopen("poj1195ans.txt","w",stdout);
    memset(tree,0,sizeof(tree));
    while (scanf("%d",&op)!=EOF)
    {
        if (op==0)
        {
            scanf("%d",&n);
            n++;
        }
        if (op==1)
        {
            scanf("%d%d%d",&x1,&y1,&a);
            add(x1+1,y1+1,a);
        }
        if (op==2)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            ans=sum(x2+1,y2+1)-sum(x2+1,y1)-sum(x1,y2+1)+sum(x1,y1);
            printf("%d\n",ans);
        }
        if (op==3) break;
    }
    return 0;
}
