#include<stdio.h>
#include<string.h>

#define MaxN   11
#define inf    0x3f3f3f3f

struct TEdge
{
    int v,c,p,r,next;
}edge[MaxN];

int head[MaxN];
int index,n,m,ans,maxcyc;
int vis[MaxN];

void DFS(int u,int cost)
{
    int i,v;
    if (cost>ans) return;
    if (u==n)
    {
        ans=cost;
        return;
    }
    
    for (i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (vis[v]<=maxcyc)  //不能超过最大环回数
        {
            vis[v]++;
            if (vis[edge[i].c]>0) DFS(v,cost+edge[i].p);
            else DFS(v,cost+edge[i].r);
            vis[v]--;
        }
    }
}

int main()
{
    int i,u,v,c,p,r;
    freopen("poj3411.txt","r",stdin);
    freopen("poj3411ans.txt","w",stdout);
    maxcyc=MaxN/3;  //最大环回数=边数/(2(来回路径)+1(省钱路径))
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        index=0;
        memset(head,-1,sizeof(head));
        for (i=0;i<m;i++)
        {
            scanf("%d%d%d%d%d",&u,&v,&c,&p,&r);
            edge[index].v=v;
            edge[index].c=c;
            edge[index].p=p;
            edge[index].r=r;
            edge[index].next=head[u];
            head[u]=index++;
        }
        memset(vis,0,sizeof(vis));
        ans=inf;
        vis[1]=1;
        DFS(1,0);
        if (ans==inf) printf("impossible\n");
        else printf("%d\n",ans);
    }
    return 0;
}
