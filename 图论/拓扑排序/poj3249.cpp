#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define MaxN 100002
#define MaxE 1000002
#define INF  0x3f3f3f3f

int val[MaxN],dp[MaxN];

/*----------TopoSort Template Start----------*/

struct TEdge
{
    int v,next;
}edge[MaxE];
int head[MaxN],index;

int ind[MaxN],oud[MaxN],pointnum;  //入度数，出度数，点数

void AddEdge(int src,int trg)
{
    edge[index].v=trg;
    edge[index].next=head[src];
    head[src]=index++;
    ind[trg]++;
    oud[src]++;
}

void InitEdge(int pn)
{
    memset(head,-1,sizeof(head));
    memset(ind,0,sizeof(ind));
    memset(oud,0,sizeof(oud));
    index=0;
    pointnum=pn;
}

void TopoSort()
{
    queue<int> q;
    int i,u,v;
    for (i=1;i<=pointnum;i++) if (ind[i]==0) //一开始所有入度为0的点都是起点 
    {
        dp[i]=val[i];
        q.push(i); 
    }
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        for (i=head[u];i!=-1;i=edge[i].next)
        {
       	    v=edge[i].v;
       	    ind[v]--;
       	    //oud[u]--;  这里保留出度信息，用于搜索答案 
       	    if (dp[u]+val[v]>dp[v]) dp[v]=dp[u]+val[v];
       	    if (ind[v]==0) q.push(v);
        }
    }
}

/*----------TopoSort Template Over----------*/

int n,m;

int main()
{
    int i,u,v,ans;
    freopen("poj3249.txt","r",stdin);
    freopen("poj3249ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        memset(dp,-INF,sizeof(dp));
        for (i=1;i<=n;i++) scanf("%d",&val[i]);
        InitEdge(n);
        for (i=1;i<=m;i++) 
        {
       	    scanf("%d%d",&u,&v);
       	    AddEdge(u,v);
        }
        ans=-INF;
        TopoSort();
        for (i=1;i<=n;i++) if (oud[i]==0 && dp[i]>ans) ans=dp[i];
        printf("%d\n",ans);
    }
    return 0;
} 
