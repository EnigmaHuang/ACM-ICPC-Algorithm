#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;

#define INF 0x3f3f3f3f
#define MaxPoint 60

struct{
    int src,trg,cap,next,pair;
}edge[MaxPoint*MaxPoint];
int dis[MaxPoint];    
int head[MaxPoint];
int ne,source,target;

int n,m,gamenum,ans,a[10],id[MaxPoint][MaxPoint];               

void AddEdge(int u, int v, int c)
{
    edge[ne].src = u;
    edge[ne].trg = v;
    edge[ne].cap = c;
    edge[ne].next = head[u];
    edge[ne].pair = ne+1;
    head[u] = ne ++;
    edge[ne].src = v;
    edge[ne].trg = u;
    edge[ne].cap = 0;
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
            q.push(edge[i].trg);
        }
    }
    if (dis[target]>0) return 1; else return 0; //汇点的DIS小于零,表明BFS不到汇点
}
 
//find代表一次增广,函数返回本次增广的流量,返回0表示无法增广   
//low是源点到现在最窄的(剩余流量最小)的边的剩余流量     
int Find(int x,int low)
{
    int i,newcap=0;
    if (x==target) return low; //是汇点，直接返回
    for (i=head[x];i>0;i=edge[i].next) 
    {
        if (edge[i].cap>0 && dis[edge[i].trg]==dis[x]+1 && (newcap=Find(edge[i].trg,min(low,edge[i].cap))))
        //   联通        ，         是分层图的下一层    ，    能到汇点(新增流量newcap<>0)    
        {
            edge[i].cap-=newcap;
            edge[edge[i].pair].cap+=newcap;
            return newcap;
        }
    }
    return 0;
}

int Dinic()
{
    int ret,newcap;
    ret=0;
    while(BFS())//要不停地建立分层图,如果BFS不到汇点才结束
    {
        //一次BFS要不停地找增广路,直到找不到为止
        while(newcap=Find(source,INF)) ret+=newcap;
    }
	return(ret); 	
} 

void ReadData()
{
    int i,j;
    char s[255],len=1,c;
    scanf("%c",&c);
    n=0; 
    while (c!='\n')
    {
        s[len++]=c;
        scanf("%c",&c);
    }
    //将胜利场次依次保存到a[] 
    for (i=1;i<=len;i++)
        if (s[i]>=48 && s[i]<=57) a[++n]=s[i]-48;
    gamenum=0;
    //id[i][j]表示i和j打的比赛的场次编号 
    for (i=1;i<=n;i++)
      for (j=i+1;j<=n;j++)
        id[i][j]=++gamenum;
    source=1+gamenum+n;
    target=source+1;
}

void BuildMap(int num)
{
    int i,j,flag[MaxPoint];
    memset(head,-1,sizeof(head));
    memset(flag,0,sizeof(flag));
    ne=1;
    //源点向所有的选手连一条边，容量为其获胜场次 
    for (i=1;i<=n;i++) AddEdge(source,i,a[i]);
    //所有的比赛向汇点连一条边，容量为1 
    for (i=n+1;i<=n+gamenum;i++) AddEdge(i,target,1);
    //如果i,j同为最强胜者，且i获胜场次少于j，则i必须赢j 
	//所以i向id[i][j]场比赛连一条容量为1的边 
	for (i=n-num+1;i<=n;i++)
        for (j=i+1;j<=n;j++)
            if (a[j]>a[i])
            {
                flag[id[i][j]]=1;
            	AddEdge(i,id[i][j]+n,1);
            }
    //其余的情况下，不确定一盘是谁赢的，则i，j都向这一场比赛连一条容量为1的边 
    for (i=1;i<=n;i++)
        for (j=i+1;j<=n;j++)
            if (!flag[id[i][j]])
            {
                AddEdge(i,id[i][j]+n,1);
                AddEdge(j,id[i][j]+n,1);
            }
}

void Solve()
{
    int i,flow;
    for (i=n;i>1;i--)
    {
        BuildMap(i);
        flow=Dinic();
        if (flow==gamenum) break;
    }
    printf("%d\n",i);
}

int main()
{
    scanf("%d\n",&m);
    while (m--)
    {
    	ReadData();
        Solve();
    }     
}
