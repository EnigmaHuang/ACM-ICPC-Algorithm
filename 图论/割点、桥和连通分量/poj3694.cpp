#include <cstdio>
#include <cstring>

#define MaxN 100005
#define MaxE 400020
#define min(a,b) (a<b)?a:b;

using namespace std;

struct TEdge
{
    int v, next;
}edge[MaxE];

int low[MaxN],dfn[MaxN],vis[MaxN];
int bridge[MaxN],father[MaxN],head[MaxN];
int cnt,n,m,index,EdgeNum;

void Init()
{
	int i;
    EdgeNum=index=cnt=0;
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(bridge,0,sizeof(bridge));
    memset(head, -1, sizeof(head));
    for(i=1;i<= n;i++) father[i]=i;
}

void AddEdge(int u, int v)
{
    edge[EdgeNum].v=v;
    edge[EdgeNum].next=head[u];
    head[u]=EdgeNum++;
}

void Tarjan(int u)
{
    int i,v;
    vis[u]=1;
    dfn[u]=low[u]=++index;
    for(i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if(!vis[v])
        {
            father[v]=u;
            Tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u])
            {
                cnt++;
                bridge[v]=1;
            }
        }
        else if(vis[v]==1 && v!=father[u]) low[u]=min(low[u],dfn[v]);
    }
    vis[u]=2;
}

void LCA(int u, int v)
{
    while(dfn[u]>dfn[v])  
    {
        if(bridge[u])  
        {
            cnt--;
            bridge[u]=0;
        }
        u=father[u];
    }
    while(dfn[v]>dfn[u])
    {
        if(bridge[v]) 
	{
            cnt--;
            bridge[v] = 0;
         }
        v=father[v];
    }
    while(u!= v)
    {
        if(bridge[u]) 
        {
            cnt--;
            bridge[u]=0;
        }
        if(bridge[v]) 
        {
            cnt--;
            bridge[v]=0;
        }
        u=father[u];
        v=father[v];
    }
}

int main()
{
    int u,v,q,cases=0;
    freopen("poj3694.txt","r",stdin);
    freopen("poj3694ans.txt","w",stdout);
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0 && m==0) break;
        printf("Case %d:\n", ++cases);
        Init();
        while(m--)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        Tarjan(1);
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d",&u,&v);
            LCA(u,v);
            printf("%d\n",cnt);
        }
        printf("\n");
    }
    return 0;
}
