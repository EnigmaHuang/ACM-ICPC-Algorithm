#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxT 1005

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

int main()
{
    int t,n,m,i,j,x1,x2,y1,y2,ans;
    char s[5];
    freopen("poj2155.txt","r",stdin);
    freopen("poj2155ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        memset(tree,0,sizeof(tree));
        for (i=0;i<m;i++)
        {
            scanf("%s",s);
            if (s[0]=='C')
            {
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                x2++;y2++;
                add(x1,y1,1);
                add(x1,y2,-1);
                add(x2,y1,-1);
                add(x2,y2,1);
            }
            else
            {
                scanf("%d%d",&x1,&y1);
                ans=sum(x1,y1);
                ans%=2;
                printf("%d\n",ans);
            }
        }
        if (t) printf("\n");
    }
    return 0;
}
