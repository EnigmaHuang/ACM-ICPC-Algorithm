#include<cstdio>
#include<cstring>
#include<cstdlib>

#define INF 0x3f3f3f3f 
#define MaxN 202
#define MaxE 10400 

using namespace std;

/*----------ISAP Template Start----------*/

struct Tedge
{      
    int next,pair;    //同一起点下一条边的编号，反向边的编号
    int trg,cap,flow; //该边指向的点，该边的剩余容量，该边的流量         
}edges[MaxE];         //边集 
int first[MaxN];      //每一个点出发的边的第一条的编号
int source,target,index,pointnum; 

int m,n; 

int level[MaxN];   //各层次有的点的数目
int dist[MaxN];    //各点到汇点距离
int nowpath[MaxN]; //当前增广路径中的各点
int pre[MaxN];     //各点的前驱

int ISAP() 
{
    //当前增广路增加的流量，总的最大流量，当前点，当前增广路瓶颈点 
    int now_flow,max_flow,now,tmp,neck,i;
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

int N,M;
int flag[MaxN];

void DFS(int u)
{
    int i,v;
    flag[u]=1;
    for (i=first[u];i!=-1;i=edges[i].next)
    {
        v=edges[i].trg;
        if (edges[i].cap && !flag[v]) DFS(v);
    }
}

int main()
{
    int i,u,v,inv,outv,MinCut,Operate;
    freopen("poj2125.txt","r",stdin);
    freopen("poj2125ans.txt","w",stdout);
    while (scanf("%d%d",&N,&M)!=EOF)
    {
    	InitISAP(0,2*N+1,2*N+2);
        for (i=1;i<=N;i++)
        {
       	    scanf("%d",&inv);
       	    AddEdge(i+N,target,inv);
        }
        for (i=1;i<=N;i++)
        {
       	    scanf("%d",&outv);
       	    AddEdge(source,i,outv);
        }
        for (i=0;i<M;i++)
        {
       	    scanf("%d%d",&u,&v);
       	    AddEdge(u,v+N,INF);
        }
        MinCut=ISAP();
        Operate=0;
        memset(flag,0,sizeof(flag));
        DFS(source);
        for (i=1;i<=N;i++)
        {
       	    if (0==flag[i])   Operate++;
       	    if (1==flag[i+N]) Operate++;
        }
        printf("%d\n",MinCut);
        printf("%d\n",Operate);
        for (i=1;i<=N;i++)
        {
       	    if (0==flag[i])   printf("%d -\n",i);
       	    if (1==flag[i+N]) printf("%d +\n",i);
        }
    }
}
