#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define Max(a,b) ((a)>(b)?(a):(b))  
#define Min(a,b) ((a)<(b)?(a):(b))  

#define MaxN 50005
#define MaxE 200005

int w[MaxN],ans[MaxN];   //点权，答案 
int min[MaxN],max[MaxN]; //从根到当前点的最小价格和最大价格 
int up[MaxN],down[MaxN]; //从当前点到根和从根到当前点的最大利润 

struct TEdge
{
    int u,v,next,id;
}edge[MaxE];

//原图边头（treehead），查询边头(queryhead) 
int thead[MaxN],qhead[MaxN],head[MaxN],index;

int father[MaxN],vis[MaxN]; //各点的父节点，访问标记

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
    memset(thead,-1,sizeof(thead));
    memset(qhead,-1,sizeof(qhead));
}

void AddTEdge(int u,int v)  //加原图边 
{
    edge[index].v=v;
    edge[index].next=thead[u];
    thead[u]=index++;
}

void AddQEdge(int u,int v,int id) //加查询边 
{
    edge[index].v=v;
    edge[index].u=u;
    edge[index].id=id;
    edge[index].next=qhead[u];
    qhead[u]=index++;
}

void AddEdge(int u,int id)
{
    edge[index].id=id;
    edge[index].next=head[u];
    head[u]=index++;
}

int Max3(int a,int b,int c)
{
    return (Max(a,Max(b,c)));
}

int Update(int u)
{
    int fa; 
    if (father[u]==u) return u;
    //这一点需要被更新
    fa=father[u];  //保留原来的父节点
    father[u]=Update(father[u]);  //更新和压缩路径 
    //DP动态更新 
    up[u]   = Max3(up[u],up[fa],max[fa]-min[u]);
    down[u] = Max3(down[u],down[fa],max[u]-min[fa]);
    //维护路径上的最大最小值 
    max[u]  = Max(max[u],max[fa]);
    min[u]  = Min(min[u],min[fa]);
    return father[u];
}

void DFS(int u)
{
    int i,fa,src,v,tmp,id;
    father[u]=u;
    for (i=thead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (!vis[v])
        {
            DFS(v);
            father[v]=u;  //并查集合并 
        } 
    }
    vis[u]=1;
    for (i=qhead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (vis[v])  //合并祖先与子孙的邻接表 
        {
            fa=Update(v);
            AddEdge(fa,i);  //辅助边，记录到哪一条查询边 
        }
    }
    for (i=head[u];i!=-1;i=edge[i].next)
    {
        tmp=edge[i].id;
        id=edge[tmp].id;
        src=edge[tmp].u;
        v=edge[tmp].v;
        Update(src);
        if (id<0)  //按u,v方向进行合并 
        {
            tmp=src;
            src=v;
            v=tmp;
            id=-id;
        }
        ans[id]=Max3(up[src],down[v],max[v]-min[src]);
    }
}

int main()
{
    int n,i,u,v,m;
    freopen("poj3728.txt","r",stdin);
    freopen("poj3728ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitEdge();
        for (i=1;i<=n;i++)
        {
            scanf("%d",&w[i]);
            min[i]=max[i]=w[i];
        }
        for (i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            AddTEdge(u,v);
        }
        scanf("%d",&m);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            AddQEdge(u,v,i);
            AddQEdge(v,u,-i);  //表明边的方向 
        }
        memset(vis,0,sizeof(vis));
        memset(up,0,sizeof(up));
        memset(down,0,sizeof(down));
        DFS(1);
        for (i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}
