#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<queue>

#define INF 0x3f3f3f3f

using namespace std;

/* SPFA mincost-flow Template Start */

const int MaxN = 50*50*2+2;
const int MaxE = 30000+20;   //其实这里我也不确定要开多少………… 

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

int n,k,ans;

void ReadData()
{
    int i,j;
    int s[51][51],id[51][51],src,trg; 
    InitMinCostFlow(0,2*n*n+1);
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++) 
        {
            scanf("%d",&s[i][j]);
            id[i][j]=((i-1)*n+j)*2;
        }
    }
    AddEdge(source,1,k,0);
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++) 
        {
        	//拆点建图 
            AddEdge(id[i][j]-1,id[i][j],k-1,0);
            AddEdge(id[i][j]-1,id[i][j],1,-s[i][j]);           //求最长路，数值取反 
            if (i+1<=n) AddEdge(id[i][j],id[i+1][j]-1,k,0);
            if (j+1<=n) AddEdge(id[i][j],id[i][j+1]-1,k,0);
        }
    }
    AddEdge(2*n*n,target,k,0);  
} 

int main()
{
    freopen("poj3422.txt","r",stdin);
    freopen("poj3422ans.txt","w",stdout);
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        ReadData();
        ans=MinCostFlow();
        printf("%d\n",-ans);		//上面数值取反，注意这里再取反 
    }
}
