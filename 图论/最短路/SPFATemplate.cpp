#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

#define INF  0x3f3f3f3f
#define MaxN 1005
#define MaxE 21005

/*---------------SPFA Template Start---------------*/
 
struct TEdge
{
    int u,v,w,next;
}edge[MaxE];
int head[MaxN],dist[MaxN],vistime[MaxN],inqueue[MaxN];
int index,nodenum;
 
void AddEdge(int src,int trg,int weight)
{
    edge[index].u=src;
    edge[index].v=trg;
    edge[index].w=weight;
    edge[index].next=head[src];
    head[src]=index++;
}

void InitMap(int n)
{
    index=1;
    memset(head,-1,sizeof(head));
    nodenum=n;
}

int SPFA(int source)
{
    int i,u,v;
    queue<int> q;
    memset(dist,INF,sizeof(dist));
    memset(vistime,0,sizeof(vistime));
    memset(inqueue,0,sizeof(inqueue));
    
    dist[source]=0;
    vistime[source]=1;
    inqueue[source]=1;
    
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        inqueue[u]=0;
        for (i=head[u];i;i=edge[i].next)
        {
            v=edge[i].v;
            if (dist[v]>dist[u]+edge[i].w)
            {
                dist[v]=dist[u]+edge[i].w;
                if (!inqueue[v])
                {
                    inqueue[v]=1;
                    q.push(v);
                    if (++vistime[v]>nodenum) return 0; //有一个点进队超过点数次说明有负环
                }
            }
        }
    }
    return 1;
}

/*---------------SPFA Template Over---------------*/

int main()
{
    freopen("","r",stdin);
    freopen("","w",stdout);
    
    return 0;
}
