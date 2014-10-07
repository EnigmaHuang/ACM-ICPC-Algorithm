#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

#define MaxN 1005
#define MaxE 100005 
#define INF  0x3f3f3f3f

struct TNode 
{
    int u,dis,val; //点编号，到源点距离，估计函数值h(n) 
    bool operator < (const TNode &a) const
    {
        return val > a.val;
    }
};

struct Edge 
{
    int v,w,next;
}Edge[MaxE], ReEdge[MaxE];
int Head[MaxN],ReHead[MaxN];
int EdgeCnt,ReEdgeCnt;

void AddEdge(int u,int v,int w)
{
    //正向边
    Edge[EdgeCnt].v=v;
    Edge[EdgeCnt].w=w;
    Edge[EdgeCnt].next=Head[u];
    Head[u]=EdgeCnt++;
    //反向边 
    ReEdge[ReEdgeCnt].v=u;
    ReEdge[ReEdgeCnt].w=w;
    ReEdge[ReEdgeCnt].next=ReHead[v];
    ReHead[v]=ReEdgeCnt++;
}

void InitEdge()
{
    memset(Head,-1,sizeof(Head));
    memset(ReHead,-1,sizeof(ReHead));
    EdgeCnt=ReEdgeCnt=0;
}

int dis[MaxN],vis[MaxN];

void SPFA(int source)
{
    queue<int> Que;
    int u,v,i;
    memset(dis,INF,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[source]=0;
    Que.push(source);
    vis[source]=1;
    while (!Que.empty())
    {
        u=Que.front();
        Que.pop();
        vis[u]=0;
        for (i=ReHead[u];i!=-1;i=ReEdge[i].next)
        {
            v=ReEdge[i].v;
            if (dis[v]>dis[u]+ReEdge[i].w) 
	    {
                dis[v]=dis[u]+ReEdge[i].w;
                if (!vis[v]) 
		{
                    vis[v]=1;
                    Que.push(v);
                }
            }
        }
    }
}

void AStar(int source,int target,int k)
{
    int u,v,cnt,i;
    TNode node,newnode;
    priority_queue<TNode> Que;
    cnt=0;
    node.u=source;
    node.dis=0;
    node.val=0;
    Que.push(node);
    if (source==target) k++;
    while (!Que.empty())
    {
        node=Que.top();
        Que.pop();
        u=node.u;
        if (u==target) 
        {
            cnt++;
            if (cnt==k) 
            {
                printf("%d\n",node.dis);  //很奇怪，不知道为什么这里这么写就能过 
                return;                   //如果是返回node.dis再输出就不行 
            } 
        }
        for (i=Head[u];i!=-1;i=Edge[i].next)
        {
            v=Edge[i].v;
            if (dis[v]==INF) continue; //该点不能到达汇点，跳过 
            newnode.u=v;
            newnode.dis=node.dis+Edge[i].w;
            /*启发式为f(n)=g(n)+h(n)，g(n)为当前距离源点
              距离即newnode.dis，h(n)为估计到汇点的距离，
              这里直接用SPFA得出的汇点到当前点的最小距离*/ 
            newnode.val=newnode.dis+dis[v];
            Que.push(newnode);
        }
    }
    if (cnt<k) printf("-1\n"); //同上，这里直接输出就可以，返回输出就不行   
}

int n,m,source,target,k;

int main()
{
    int u,v,w,cnt,i;
    freopen("poj2449.txt","r",stdin);
    freopen("poj2449ans.txt","w",stdout);
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        scanf("%d%d%d",&source,&target,&k);
        SPFA(target);
        if(dis[source]==INF) 
	{
            printf("-1\n");
            continue;
        }
        AStar(source,target,k);
    }
    return 0;
}
