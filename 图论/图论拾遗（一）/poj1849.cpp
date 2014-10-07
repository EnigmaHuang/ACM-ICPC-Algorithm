#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;

#define MaxN 100001
#define MaxE 100001

struct
{
    int v,w,next;
}edge[MaxE];

int n,s,maxp;

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
    freopen("poj1849.txt","r",stdin);
    freopen("poj1849ans.txt","w",stdout);
    while (scanf("%d%d",&n,&s)!=EOF)
    {
        memset(head,-1,sizeof(head));
        index=0;
        ans=0;
        n--;
        while (n--)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
            ans+=2*w;
        }
        BFS(s);
        ans-=BFS(maxp);
        printf("%d\n",ans);
    }
    return 0;
}
