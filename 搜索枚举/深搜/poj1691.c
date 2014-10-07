#include<stdio.h>
#include<string.h>

#define MaxN 16
#define inf  0x3f3f3f3f


struct TRect
{
    int x1,y1,x2,y2,c;
}rect[MaxN];

int n,ans,deg[MaxN];
int vis[MaxN],edge[MaxN][MaxN];

void BuildMap()
{
    int i, j;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            if ((rect[i].y2==rect[j].y1) &&
               !(rect[i].x2<rect[j].x1 || rect[i].x1>rect[j].x2))
            {
                deg[j]++;
                edge[i][j]=1;
            }
}

void DFS(int depth,int sum,int color)
{
    int i,j;
    if (sum>ans) return;
    if (depth==n)
    {
        ans=sum;
        return;
    }
    for (i=0;i<n;i++) if (!vis[i] && deg[i]==0)
    {
        vis[i]=1;
        //删去i起点为i的边
        for (j=0;j<n;j++) if (edge[i][j]) deg[j]--;

        if (rect[i].c==color) DFS(depth+1,sum,color);
        else DFS(depth+1,sum+1,rect[i].c);

        //回滚操作
        for (j=0;j<n;j++) if (edge[i][j]) deg[j]++;
        vis[i]=0;
    }
}

int main()
{
    int t, i, j;
    freopen("poj1691.txt","r",stdin);
    freopen("poj1691ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        memset(edge,0,sizeof(edge));
        memset(deg,0,sizeof(deg));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&rect[i].y1,&rect[i].x1);
            scanf("%d%d%d",&rect[i].y2,&rect[i].x2,&rect[i].c);
        }
        BuildMap();
        ans=inf;
        DFS(0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
