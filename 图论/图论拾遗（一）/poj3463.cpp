#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>

using namespace std;

#define inf  0x3f3f3f3f 
#define MaxN 1005
#define MaxE 10050

int dis[MaxN][2],cnt[MaxN][2],vis[MaxN][2];

struct edge
{
    int u,v,dis,next;
}edge[MaxE];
int head[MaxN],index,source,target;

struct Node
{
    int u;
    int flag;             //表示节点类型，0表示最短，1表示次短
    bool operator < (const Node &a)const
    {
        return dis[u][flag]>dis[a.u][a.flag];
    }
};

void AddEdge(int u,int v,int w)
{
    edge[index].u=u;
    edge[index].v=v;
    edge[index].dis=w;
    edge[index].next=head[u];
    head[u]=index++;
}

void InitEdge()
{
    memset(head,-1,sizeof(head));
    index=0;
}

int Dijkstra()
{
    int u,flag,i,to,dist; 
    Node top,newnode;
    priority_queue<Node>Q;
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    memset(dis,inf,sizeof(dis));
    newnode.u=source;
    newnode.flag=0;
    Q.push(newnode);
    dis[source][0]=0;
    cnt[source][0]=1;
    while(!Q.empty())
    {
        top=Q.top();
        Q.pop();
        u=top.u;
        flag=top.flag;
        if (vis[u][flag]) continue;          //u点已经完成了松弛操作，跳过 
        for (i=head[u];i!=-1;i=edge[i].next) //遍历u点的出边 
        {
            to=edge[i].v;
            dist=dis[u][flag]+edge[i].dis;
            if (dist<dis[to][0])             //如果找到路径比原最短路还短
            {
                if (dis[to][0]!=inf)         //原来已经找到了最短路的情况下
                {
                    dis[to][1]=dis[to][0];   //原最短路置为次短路                
                    cnt[to][1]=cnt[to][0];   //原次短路条数置为次短路条数
                    newnode.u=to;
                    newnode.flag=1;
                    Q.push(newnode);         //当前点u的次短距离已被更新，重新入队 
                }                                          
                dis[to][0]=dist;             //更新u的最短距离
                cnt[to][0]=cnt[u][flag];     //更新最短路条数，由上一点的最/次短路条数决定 
                newnode.u=to;
                newnode.flag=0;
		Q.push(newnode);
            }
            else if (dist==dis[to][0])       //如果找到路径的距离和原最短路相同
            {
                cnt[to][0]+=cnt[u][flag];    //增加最短路径条数，但不需要入队更新 
            }
            else if (dist<dis[to][1])        //如果找到路径比原次短路短
            {
                dis[to][1]=dist;             //更新次短路
                cnt[to][1]=cnt[u][flag];     //增加次短路条数
                newnode.u=to;
                newnode.flag=1;
		Q.push(newnode);             //入队更新 
            }
            else if (dist==dis[to][1])       //如果找到路径和次短路相同
            {
                cnt[to][1]+=cnt[u][flag];    //增加次短路条数 
            }
        }
        vis[u][flag]=1;                      //u点完成了松弛操作，标记之 
    }
    if (dis[target][0]+1==dis[target][1]) return cnt[target][0]+cnt[target][1];
    return cnt[target][0];
}

int n,m;

int main()
{
    int t,u,v,w;
    freopen("poj3463.txt","r",stdin);
    freopen("poj3463-2ans.txt","w",stdout);
    scanf("%d",&t);
    while(t--)
    {
        InitEdge(); 
        scanf("%d%d",&n,&m);
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        scanf("%d%d",&source,&target);
        printf("%d\n",Dijkstra());
    }
    return 0;
}
