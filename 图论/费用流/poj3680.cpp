#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<queue>

#define INF 0x3f3f3f3f

using namespace std;

/* SPFA mincost-flow Template Start */

const int MaxN = 410;
const int MaxE = 1640;   //其实这里我也不确定要开多少………… 

struct
{
	int u,v,cap,cost,next,pair;
}edges[MaxE];
int head[MaxN],pre[MaxN];
int source,target,index;

void AddEdge(int src,int trg,int cap,int cst)
{
    index++;
    edges[index].u=src;
    edges[index].v=trg;
    edges[index].cap=cap;
    edges[index].cost=cst;
    edges[index].next=head[src];
    edges[index].pair=index+1; 
    head[src]=index;
    index++;
    edges[index].u=trg;
    edges[index].v=src;
    edges[index].cap=0;
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

struct line
{
	int st,ed,w;
}ln[MaxN];

int n,k; 

void ReadData()
{
    int hash[100000];
    int i,nodenum=1;
    memset(hash,0,sizeof(hash));
    scanf("%d%d",&n,&k);
    for (i=1;i<=n;i++)
    {
        scanf("%d%d%d",&ln[i].st,&ln[i].ed,&ln[i].w);
        hash[ln[i].st]=hash[ln[i].ed]=1;
    } 
    for (i=1;i<=100000;i++)
    {
        if (1==hash[i])
        {
            hash[i]=nodenum;
            nodenum++;
        }
    }
    for (i=1;i<=n;i++)
    {
        ln[i].st=hash[ln[i].st];
        ln[i].ed=hash[ln[i].ed];
    }
    InitMinCostFlow(0,nodenum);
    for (i=0;i<nodenum;i++) AddEdge(i,i+1,k,0);
    for (i=1;i<=n;i++) AddEdge(ln[i].st,ln[i].ed,1,-ln[i].w);
}

int main()
{
    int t;
    freopen("poj3680.txt","r",stdin);
    freopen("poj3680ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        ReadData();
        printf("%d\n",-MinCostFlow());
    }
}
