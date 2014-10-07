#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define MaxN 101
#define MaxE 1001

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
    for (i=1;i<=pointnum;i++) if (ind[i]==0) q.push(i);
    while (!q.empty())
    {
        u=q.front();
        /*Do something about it*/
        q.pop();
        for (i=head[u];i!=-1;i=edge[i].next)
        {
       	    v=edge[i].v;
       	    ind[v]--;
       	    oud[u]--;
       	    if (ind[v]==0) q.push(v);
        }
    }
}

/*----------TopoSort Template Over----------*/

int main()
{
    int i;
    freopen("","r",stdin);
    freopen("","w",stdout);
    
    return 0;
} 
