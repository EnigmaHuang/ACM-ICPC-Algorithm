#include <stdlib.h> 
#include <stdio.h>  
#include <string.h> 

#define min(a,b) (a<b)?a:b;
#define MaxN 2*205 
#define MaxE 2*205*205 
#define INF  0x3F3F3F3F  

/*----------ISAP Template Start----------*/

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

int n,map[201][201],ans[201];

int del[201];

void BuildMap()
{
    int i,j;
    for (i=1;i<=n;i++)
    {
        if (del[i]) continue;
        for (j=1;j<=n;j++)
        {
       	   if (del[j]) continue; 
       	   if (i==j) AddEdge(i,i+n,1);
           else if (map[i][j]) AddEdge(i+n,j,INF);
        }
    }
    
}

int main()
{
    int i,j,MinCut,k,NewMinCut,num,score;
    freopen("poj1815.txt","r",stdin);
    freopen("poj1815ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&source,&target)!=EOF)
    {
        InitISAP(source+n,target,2*n);
        memset(del,0,sizeof(del));
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++) scanf("%d",&map[i][j]);
            
        if (map[source-n][target]) 
        {
       	    printf("NO ANSWER!\n");
       	    continue;
        }
        
        BuildMap();
        MinCut=ISAP();
        printf("%d\n",MinCut);
        num=0;
        for (i=1;i<=n;i++)
        {
       	    if (i==source-n || i==target) continue; 
       	    del[i]=1;
       	    InitISAP(source,target,2*n); 
       	    BuildMap();
       	    NewMinCut=ISAP();
       	    if (NewMinCut==MinCut-1) MinCut=NewMinCut;
       	    else del[i]=0;
        }
        for (i=1;i<=n;i++) if (del[i]) printf("%d ",i);
        printf("\n");
    }
}
