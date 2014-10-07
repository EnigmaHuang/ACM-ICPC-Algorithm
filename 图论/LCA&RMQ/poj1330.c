#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MaxN 10005

/*----------LCA Tarjan Template Start----------*/

struct TEdge
{
    int u,v,next;
}edge[MaxN];
int head[MaxN],index;

int father[MaxN],vis[MaxN]; //各点的父节点，访问标记
int qx,qy,root,ans;         //查询的两个点，根节点，查询结果 

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    edge[index].u=u;
    edge[index].v=v;
    edge[index].next=head[u];
    head[u]=index++;
}

int GetFather(int x)
{
    if (father[x]==x) return x;
    father[x]=GetFather(father[x]);
    return father[x];
}

void Union(int x,int y)
{
    int fx,fy;
    fx=GetFather(x);
    fy=GetFather(y);
    if (fx==fy) return; else father[y]=fx;
}

void DFS(int u)
{
    int i,res;
    for (i=head[u];i!=-1;i=edge[i].next)
    {
        DFS(edge[i].v);
        Union(u,edge[i].v);
        vis[edge[i].v]=1;
    }
    if (qx==u && vis[qy]) ans=GetFather(qy);         
    else if (qy==u && vis[qx]) ans=GetFather(qx);
}

void InitLCATarjan()
{
    memset(vis,0,sizeof(vis));
}

void LCATarjan(int n,int u,int v)
{
    int i;
    for (i=1;i<=n;i++) 
    {
        if (!vis[i]) root=i;
        father[i]=i;
    }
    memset(vis,0,sizeof(vis));
    qx=u;qy=v;
    DFS(root);
}

/*----------LCA Tarjan Template Over----------*/

int main()
{
    int n,t,u,v,i;
    freopen("poj1330.txt","r",stdin);
    freopen("poj1330ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        InitEdge();
        scanf("%d",&n);
        InitLCATarjan();
        for (i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            vis[v]=1;
        }
        scanf("%d%d",&u,&v);
        LCATarjan(n,u,v);
        printf("%d\n",ans);
    }
    return 0;
}
