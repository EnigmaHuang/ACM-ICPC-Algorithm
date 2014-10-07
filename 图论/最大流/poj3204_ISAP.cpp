#include <stdlib.h> 
#include <stdio.h>  
#include <string.h> 
#include <vector>

#define min(a,b) (a<b)?a:b;
#define MaxN 1000
#define MaxE 50000
#define INF  0x3F3F3F3F  

/*----------ISAP Template Start----------*/

using namespace std;

struct TEdge
{      
    int next,pair,trg;//同一起点下一条边的编号，反向边的编号，该边指向的点 
    int cap;          //该边的剩余容量       
}edges[MaxE];         //边集 
int first[MaxN];      //每一个点出发的边的第一条的编号
int source,target,index,pointnum; 

int level[MaxN];   //各层次有的点的数目
int dist[MaxN];    //各点到汇点距离
int nowpath[MaxN]; //当前增广路径中的各点
int pre[MaxN];     //各点的前驱

int ISAP() 
{
    //当前增广路增加的流量，总的最大流量，当前点，当前增广路瓶颈点 
    int now_flow,max_flow,now,neck,tmp,i;
    memset(dist,0,sizeof(dist));    
    memset(level,0,sizeof(level));
    memset(pre,-1,sizeof(pre));
    for(i=1;i<=pointnum;++i)  nowpath[i]=first[i];
    level[target]=pointnum;
    max_flow=0;
    now=source;
    while(dist[source]<pointnum)     
    {   //如果当前点已经到了目的点，增广路寻找完毕         
        if(now==target)         
        {
            //寻找增广路中的最大允许增加流量，同时标记瓶颈点 
            now_flow=INF;
            for(i=source;i!=target;i=edges[nowpath[i]].trg)
            {
                if(now_flow>edges[nowpath[i]].cap)
                {
                    neck=i;
                    now_flow=edges[nowpath[i]].cap;
                }
            }
            //更新增广路上各路径的流量信息   
            for(i=source;i!=target;i=edges[nowpath[i]].trg)
            {
                tmp=nowpath[i];
                edges[tmp].cap-=now_flow;
                tmp=edges[tmp].pair;
                edges[tmp].cap+=now_flow;
            }
            max_flow+=now_flow;
            if (now_flow==INF) return(now_flow);
            now=neck; 
        }          
        
        //如果当前未找完增广路 
        
        //对当前点找一条可用边        
        for(i=nowpath[now];i!=-1;i=edges[i].next)
            if(edges[i].cap>0 && dist[now]==dist[edges[i].trg]+1) break;

        if(i!=-1)   //有可用边，使用并记录    
        {
            nowpath[now]=i;
            pre[edges[i].trg]=now;
            now=edges[i].trg;
        }
        else        //没有可用边 
        {
            level[dist[now]]--;
            if(0==level[dist[now]]) break;  //出现断层，终止算法并返回 
            nowpath[now]=first[now];        //删除当前增广路的一个记录并恢复初始值 
            //遍历所有当前点指向的点，找其中层次最小的
            tmp=pointnum; 
            for (i=first[now];i!=-1;i=edges[i].next)
              if(edges[i].cap>0)
                tmp=tmp<dist[edges[i].trg]?tmp:dist[edges[i].trg];
            dist[now]=tmp+1;             //更新当前点的层次 
            ++level[dist[now]];       //更新当前点层次的点数 
            if(now!=source) now=pre[now];  //回溯到当前点的前驱点 
        }
    }
    return max_flow;
}

void AddEdge(int u,int v,int c)
{
    edges[index].next=first[u];
    edges[index].trg=v;
    edges[index].cap=c;
    edges[index].pair=index+1;
    first[u]=index++;
    edges[index].next=first[v];
    edges[index].trg=u;
    edges[index].cap=0;
    edges[index].pair=index-1;
    first[v]=index++;	
}

void InitISAP(int S,int T,int Num)
{
    index=0;
    source=S;
    target=T;
    pointnum=Num;
    memset(first,-1,sizeof(first));
}

/*----------ISAP Template Over----------*/

int n,m;
int u[MaxE],v[MaxE];
int SSet[MaxN],TSet[MaxN];  //最小割后属于源的集合和汇的集合 

vector <int> ef[MaxN],eb[MaxN];  //前后向的边，用于搜索 

void DFSF(int u)
{
    int i,v;
    SSet[u]=1;
    for (i=0;i<ef[u].size();i++)
    {
       v=ef[u][i];
       if (!SSet[v]) DFSF(v);
    }
}

void DFSB(int u)
{
    int i,v;
    TSet[u]=1;
    for (i=0;i<eb[u].size();i++)
    {
       v=eb[u][i];
       if (!TSet[v]) DFSB(v);
    }
}

int main()
{
    int i,w,eid,ans;
    freopen("poj3204.txt","r",stdin);
    freopen("poj3204ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitISAP(0,n-1,n);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u[i],&v[i],&w);
            AddEdge(u[i],v[i],w);
        }
        ISAP();
        for (i=0;i<MaxN;i++)  //清空向量 
        {
            ef[i].clear();
            eb[i].clear();
        }
        for (i=0;i<index;i+=2) if (edges[i].cap) //如果还有残余流量，作为可用边 
		{
		    eid=i/2+1;  //取原始边而非对偶反向边编号
		    ef[u[eid]].push_back(v[eid]); //正向搜索图加边 
		    eb[v[eid]].push_back(u[eid]); //反向搜索图加边 
		}
		memset(SSet,0,sizeof(SSet));
		memset(TSet,0,sizeof(TSet));
		DFSF(source); //正向搜索染色 
		DFSB(target); //反向搜索染色 
		ans=0;
		for (i=0;i<index;i+=2) if (edges[i].cap==0) //搜索符合的边
		{
		    eid=i/2+1;
		    if (SSet[u[eid]] && TSet[v[eid]]) ans++;
		}
		printf("%d\n",ans);
    }
    return 0;
}
