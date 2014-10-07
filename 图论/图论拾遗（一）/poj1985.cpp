#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;

#define MaxN 50001
#define MaxE 100001

struct
{
    int v,w,next;
}edge[MaxE];

int n,m,maxp;

int index,head[MaxN],dis[MaxN];

void AddEdge(int u,int v,int w)
{
    edge[index].v=v;
    edge[index].w=w;
    edge[index].next=head[u];
    head[u]=index++;
}

int BFS(int source)
{
    int i,u,v,max=0;
    queue<int> q;
    memset(dis,-1,sizeof(dis));
    dis[source]=0;
    q.push(source);
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        for (i=head[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].v;
            if (dis[v]==-1)
            {
                dis[v]=dis[u]+edge[i].w;
                if(dis[v]>max)
                {
                    max=dis[v];
                    maxp=v;
                }
                q.push(v);
            }
        }
    }
    return max;
}

int main()
{
    int u,v,w,ans;
    char c;
    freopen("poj1985.txt","r",stdin);
    freopen("poj1985ans.txt","w",stdout);
    while (scanf("%d%d\n",&n,&m)!=EOF)
    {
        memset(head,-1,sizeof(head));
        index=0;
        while(m--)
        {
            scanf("%d %d %d %c\n",&u,&v,&w,&c);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        BFS(1);
        ans=BFS(maxp);
        printf("%d\n",ans);
    }
    return 0;
}
