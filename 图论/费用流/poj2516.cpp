#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<queue>

#define INF 0x3f3f3f3f

#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;

/* SPFA mincost-flow Template Start */

const int MaxN=110;
 
int ans,source,target,nodenum;
int cost[MaxN][MaxN],cap[MaxN][MaxN],pre[MaxN];
 
int SPFA()
{
    int i,u;
    int vis[MaxN],dis[MaxN];
    queue<int> q;
    memset(vis,0,sizeof(vis));
    memset(dis,INF,sizeof(dis));
    dis[source]=0;
    q.push(source);
    while(!q.empty())
    {
        u=q.front();
        q.pop();
        vis[u]=true;
        for(i=source;i<=nodenum;i++)
        {
            if(cap[u][i] && dis[i]>dis[u]+cost[u][i])
            {
                dis[i]=dis[u]+cost[u][i];
                pre[i]=u;
                if(!vis[i])
                {
                    vis[i]=1;
                    q.push(i);
                }
            }
        }
        vis[u]=0;
    }
    if(dis[target]==INF) return 0;else return 1;
}
 
int Augment()
{
    int i,minflow=INF,cst=0;
    for(i=target;i!=source;i=pre[i]) minflow=min(minflow,cap[pre[i]][i]);
    for(i=target;i!=source;i=pre[i])
    {
        cap[pre[i]][i]-=minflow;
        cap[i][pre[i]]+=minflow;
        cst+=cost[pre[i]][i]*minflow;
    }
    return(cst);
}

void InitMinCostFlow(int u,int v,int n)
{
    source=u;
    target=v;
    nodenum=n;
}

/* SPFA mincost-flow Template Over */

int N,M,K,flag;
int need[MaxN][MaxN],NeedK[MaxN];
int have[MaxN][MaxN],HaveK[MaxN];

void ReadData()
{
    int i,j,k;
    memset(NeedK, 0, sizeof(NeedK));
    memset(HaveK,0,sizeof(HaveK));
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=K;j++)
        {
            scanf("%d", &need[i][j]);  //第i个客户需要第j种货物的量
            NeedK[j]+=need[i][j];      //第j种货物总共需要的量
        }
    }
    for(i=1;i<=M;i++)
    {
        for(j=1;j<=K;j ++)
        {
            scanf("%d",&have[i][j]);  //第i个仓库存储第j种货物的量
            HaveK[j]+=have[i][j];     //第j种货物总共需要的量
        }
    }
}

void Solve()
{
    int i,j,k;
    flag=1;
    for(i=1;i<=K;i++)                 //判断所有货物是否足够
    {
        if(NeedK[i]>HaveK[i])
        {
            flag=0;
            break;
        }
    }
    ans=0;
    InitMinCostFlow(0,N+M+1,N+M+1);
    for(k=1;k<=K;k++)
    {
        memset(cap,0,sizeof(cap));
        for(i=1;i<=N;i++)         //  建图。
            for(j=1;j<=M;j++)
            {
                scanf("%d",&cost[j][M+i]);
                cost[M+i][j]=-cost[j][M+i];
                cap[j][M+i]=INF;
            }
        if(!flag) continue;
        for(i=1;i<=M;i++)
        {
            cap[source][i]=have[i][k];
            cost[source][i]=cost[i][source]=0;
        }
        for(i=1;i<=N;i++)
        {
            cap[M+i][target]=need[i][k];
            cost[M+i][target]=cost[target][M+i]=0;
        }
        while(SPFA()) ans+=Augment();            //最小费用最大流
    }
}

int main()
{
    freopen("poj2516.txt","r",stdin);
    freopen("poj2516ans.txt","w",stdout);
    while(scanf("%d%d%d",&N,&M,&K) && N)
    {
        ReadData();
        Solve();
        if(flag) printf("%d\n",ans);else printf("-1\n",ans);
    }
    return 0;
}
