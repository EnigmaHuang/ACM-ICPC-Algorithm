#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define min(x,y) ((x<y)?(x):(y))
#define max(x,y) ((x>y)?(x):(y))

#define INF 0x3f3f3f3f
#define MaxPoint 210 

struct{
    int src,trg,cap,next,pair,len;
}edge[MaxPoint*MaxPoint*2];

int dis[MaxPoint];               //距源点距离，即分层图      
int n,p,t,ne,source,target,maxlen,minlen;                  
int head[MaxPoint];

void addedge(int u, int v, int c,int l)
{
    edge[ne].src = u;
    edge[ne].trg = v;
    edge[ne].cap = c;
    edge[ne].len = l;
    edge[ne].next = head[u];
    edge[ne].pair = ne+1;
    head[u] = ne ++;
    edge[ne].src = v;
    edge[ne].trg = u;
    edge[ne].cap = 0;
    edge[ne].len = l;
    edge[ne].next = head[v];
    edge[ne].pair = ne-1;
    head[v] = ne ++;
}

int BFS()   
{
    int i,j;
    queue<int> q;
    memset(dis,0xff,sizeof(dis));  //以-1填充作为未访问的标记   
    dis[source]=0;                 //源点的分层为0
    q.push(source);
    while (!q.empty())
    {
        i=q.front();
        q.pop();
        for (i=head[i];i>0;i=edge[i].next) if (dis[edge[i].trg]<0 && edge[i].cap>0)
        {
            dis[edge[i].trg]=dis[edge[i].src]+1;
            if (edge[i].trg==target) break; 
            q.push(edge[i].trg);
        }
    }
    if (dis[target]>0) return 1; else return 0; //汇点的DIS小于零,表明BFS不到汇点
}
 
//find代表一次增广,函数返回本次增广的流量,返回0表示无法增广   
//low是源点到现在最窄的(剩余流量最小)的边的剩余流量     
int find(int x,int low)
{
    int i,newcap=0;
    if (x==target) return low; //是汇点，直接返回
    for (i=head[x];i>0;i=edge[i].next) 
    {
        if (edge[i].cap>0 && dis[edge[i].trg]==dis[x]+1 && (newcap=find(edge[i].trg,min(low,edge[i].cap))))
        //   联通        ，         是分层图的下一层    ，    能到汇点(新增流量newcap<>0)    
        {
            edge[i].cap-=newcap;
            edge[edge[i].pair].cap+=newcap;
            return newcap;
        }
    }
    return 0;
}

void ReadData()
{
    int i,u,v,l;
    memset(head,-1,sizeof(head));
    ne=1;
    maxlen=0;
    minlen=INF;
    for (i=1;i<=p;i++)
    {
	scanf("%d%d%d",&u,&v,&l);
	addedge(u,v,0,l);
	maxlen=max(l,maxlen);
	minlen=min(l,minlen);
    }
    source=1;
    target=n; 
}

int Dinic()
{
    int newcap,ans=0;
    while(BFS())//要不停地建立分层图,如果BFS不到汇点才结束
    {
        //一次BFS要不停地找增广路,直到找不到为止
        while(newcap=find(1,INF)) ans+=newcap;
    }    
    return ans;	 
}

void Solve()
{
    int l,r,mid,i,ncap;
    l=minlen;
    r=maxlen;
    while (l<r)
    {
        mid=(l+r)/2;
        for (i=1;i<=ne;i++)
            if (edge[i].len<=mid) edge[i].cap=1; 
            else edge[i].cap=0;
        ncap=Dinic();
        if (ncap>=t) r=mid; else l=mid+1;	 
    }	 
    printf("%d\n",l);
}

int main()
{
    freopen("poj2455.txt" ,"r",stdin);
    freopen("poj2455ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&p,&t)!=EOF)
    {
    	ReadData(); 
    	Solve();
    }     
}
