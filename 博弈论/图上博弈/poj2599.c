#include<stdio.h>
#include<string.h>

#define MaxN 1005

int map[MaxN][MaxN];
int vis[MaxN];
int n,ans;

int DFS(int x)
{
    int i;
    vis[x]=1;
    for (i=1;i<=n;i++) if (map[x][i] && !vis[i])
    {
        vis[i]=1;
        if (DFS(i)==0)
        {
            vis[i]=0;
            ans=i;
            return 1;
        }
        vis[i]=0;
    }
    return 0;
}

int main()
{
    int i,k,u,v;
    freopen("poj2599.txt","r",stdin);
    freopen("poj2599ans.txt","w",stdout);
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        memset(map,0,sizeof(map));
        memset(vis,0,sizeof(vis));
        for (i=0;i<n-1;i++)
        {
            scanf("%d%d",&u,&v);
            map[u][v]=map[v][u]=1;
        }
        if (DFS(k)) printf("First player wins flying to airport %d\n",ans);
        else printf("First player loses");
    }
    return 0;
}
