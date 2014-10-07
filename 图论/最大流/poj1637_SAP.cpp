#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;
#define MAXN 205 
#define MAXE 2500   
#define INF 0x3f3f3f3f 

struct edge
{      
    int next,pair;    //同一起点下一条边的编号，反向边的编号
    int trg,cap,flow; //该边指向的点，该边的剩余容量，该边的流量         
}edges[MAXE];         //边集 
int first[MAXN];      //每一个点出发的边的第一条的编号
int source,target,index,pointnum; 

struct link
{
    int u,v,d;
}links[MAXE];

int ind[MAXN]; 

int m,s,has_odd_point,fullflow;

int SAP() 
{
    //各层次有的点的数目，各点到汇点距离，当前增广路径中的各点，各点的前驱
    int level[MAXN],dist[MAXN],nowpath[MAXN],pre[MAXN];
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

void InitSAP()
{
    index=0;
    memset(first,-1,sizeof(first));
}

void ReadData()
{
    int src,trg,dt,i;
    scanf("%d %d",&m,&s);
    source=m+1;
    target=source+1;
    pointnum=target;
    index=1;
    for (i=1;i<=s;i++) 
    {
        scanf("%d %d %d",&src,&trg,&dt);
        links[index].u=src;
        links[index].v=trg;
        links[index++].d=dt;
    }
}

void AddEdges()
{
    int i;
    memset(ind,0,sizeof(ind));
    for (i=1;i<=s;i++)
    {
    	ind[links[i].u]--;
    	ind[links[i].v]++;
    	if (!links[i].d) AddEdge(links[i].u,links[i].v,1);
    }
    has_odd_point=0;
    fullflow=0;
    for (i=1;i<=m;i++) if (ind[i] & 1)
    {
    	has_odd_point=1;
    	return;
    }
    for (i=1;i<=m;i++)	
    {
    	if (ind[i]<0) AddEdge(source,i,(-ind[i])/2);
        if (ind[i]>0)
        {
       	    AddEdge(i,target,ind[i]/2);
       	    fullflow+=ind[i]/2;
        }
    }
}

int Solve()
{
    if (has_odd_point) return(0);
    if (SAP()<fullflow) return(0); else return(1);
}

int main() 
{
    freopen("poj1637.txt","r",stdin);
    freopen("poj1637ans.txt","w",stdout);
    long testcase;
    scanf("%d\n",&testcase);
    while(testcase--)
    {
    	ReadData();
    	InitSAP();
    	AddEdges();
    	if (Solve()) printf("possible\n"); else printf("impossible\n"); 
    }
    return 0;
}
