#include<iostream>
#include<cstdio>
#include<memory.h>
#include<cmath>
using namespace std;
#define MAXN 201
#define MAXE 201*201*2   
#define INF 0x7fffffff
long m,n,tmp,source,target,index,pointnum;   

struct edges
{
    long next,pair;    //同一起点下一条边的编号，反向边的编号
    long trg,cap,flow; //该边指向的点，该边的剩余容量，该边的流量         
}edges[MAXE];          //边集 

long first[MAXN];      //每一个点出发的边的第一条的编号

long SAP() 
{
    //各层次有的点的数目，各点到汇点距离，当前增广路径中的各点，各点的前驱
    long level[MAXN],dist[MAXN],nowpath[MAXN],pre[MAXN];
    //当前增广路增加的流量，总的最大流量，当前点，当前增广路瓶颈点 
    long now_flow,max_flow,now,tmp,neck,i;
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
            nowpath[now]=first[now];        //删除当前增广路的一个记录并恢复初始

值 
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

int main() 
{
    freopen("poj1273.txt","r",stdin);
    freopen("poj1273ans.txt","w",stdout);
    index=0;
    long i,j,a,b,val;
    long c[MAXN][MAXN];
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        s=1;
        t=n;
        memset(c,0,sizeof(c));
        memset(first,-1,sizeof(first));
        for(i=0;i<m;++i)
        {
            scanf("%ld%ld%ld",&a,&b,&val);
            c[a][b]+=val;
        }
        for(i=1;i<=n;++i)
            for(j=i;j<=n;++j) if(c[i][j]||c[j][i])
            {
                //添加正向边  
                edges[index].next=first[i];
                edges[index].trg=j;
                edges[index].cap=c[i][j];
                edges[index].flow=0;
                edges[index].pair=index+1;
                first[i]=index++;
                //添加反向边
                edges[index].next=first[j];
                edges[index].trg=i;
                edges[index].cap=c[j][i];
                edges[index].flow=0;
                edges[index].pair=index-1;
                first[j]=index++;
            }
        printf("%ld\n",SAP());
    }
    return 0;
}
