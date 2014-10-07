#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<queue>

#define INF 0x3f3f3f3f

using namespace std;

/* SPFA mincost-flow Template Start */

const int MaxN = 210;
const int MaxE = 2*MaxN*MaxN;

struct
{
	int u,v,cap,cost,next,pair;
}edges[MaxE];
int head[MaxN],pre[MaxN];
int source,target,index;

void AddEdge(int src,int trg,int cap1,int cap2,int cst)
{
    index++;
    edges[index].u=src;
    edges[index].v=trg;
    edges[index].cap=cap1;
    edges[index].cost=cst;
    edges[index].next=head[src];
    edges[index].pair=index+1; 
    head[src]=index;
    index++;
    edges[index].u=trg;
    edges[index].v=src;
    edges[index].cap=cap2;
    edges[index].cost=-cst;
    edges[index].next=head[trg];
    edges[index].pair=index-1; 
    head[trg]=index;
}

int SPFA()
{
    queue<int> q;
    int vis[MaxN],dis[MaxN],i,u,v;
    memset(vis,0,sizeof(vis));
    memset(dis,INF,sizeof(dis));
    dis[source]=0;
    vis[source]=1;
    q.push(source);
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        for (i=head[u];i!=-1;i=edges[i].next)
        {
            v=edges[i].v;
            if (edges[i].cap && dis[v]>dis[u]+edges[i].cost)
            {
                dis[v]=dis[u]+edges[i].cost;
                pre[v]=i;
                if (!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
                } 
            }
        }
        vis[u]=0;
    }
    if (dis[target]==INF) return 0; else return 1;
}

int Augment()
{
    int u,p,minflow=INF,mincost=0;
    for (u=target;u!=source;u=edges[edges[p].pair].v)
    {
        p=pre[u];
        if (minflow>edges[p].cap) minflow=edges[p].cap;
    } 
    for (u=target;u!=source;u=edges[edges[p].pair].v)
    {
        p=pre[u];
        edges[p].cap-=minflow;
        edges[edges[p].pair].cap+=minflow;
        mincost+=minflow*edges[p].cost;
    }
    return(mincost);
}

int MinCostFlow()
{
    int ans=0,newcost;
    while (SPFA())
    {
        newcost=Augment();
        ans+=newcost;
    } 
    return(ans); 
}

void InitMinCostFlow(int u,int v)
{
    source=u;
    target=v;
    index=0;
    memset(head,-1,sizeof(head));
}

/* SPFA mincost-flow Template Over */

struct
{
    int x,y;
}house[MaxN],man[MaxN];

int n,m,numh,numm;

void ReadData()
{
    int i,j,dis;
    char c;
    numh=numm=0;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++)
        {
            scanf("%c",&c);
            if ('H'==c)
            {
                numh++;
                house[numh].x=i;
                house[numh].y=j;
            }
            else if ('m'==c)
            {
                numm++;
                man[numm].x=i;
                man[numm].y=j;
            }
        }
        scanf("\n");
    }
    InitMinCostFlow(0,numm+numh+1);
    for (i=1;i<=numm;i++) AddEdge(source,i,1,0,0);
    for (j=1;j<=numh;j++) AddEdge(j+numm,target,1,0,0);
    for (i=1;i<=numm;i++)
    {
        for (j=1;j<=numh;j++)
        {
            dis=abs(man[i].x-house[j].x)+abs(man[i].y-house[j].y);
            AddEdge(i,j+numm,1,0,dis); 
        }
    }
}

int main()
{
    freopen("poj2195.txt","r",stdin);
    freopen("poj2195ans.txt","w",stdout);
    while(scanf("%d%d\n",&n,&m)!=EOF)
    {
        if (0==n && 0==m) break;
        ReadData();
        printf("%d\n",MinCostFlow());
    }
    return 0;
} 
