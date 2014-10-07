#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define MAXN 201
#define MAXE 201*201*2   
#define INF 0x3f3f3f3f

long tmp,source,target,index,pointnum;   

struct edge{      
    long next,pair;    //同一起点下一条边的编号，反向边的编号
    long trg,cap,len; //该边指向的点，该边的剩余容量，该边的流量         
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

void BuildMap(int l)
{
    int i;
    for (i=0;i<index;i++) 
        if (edges[i].len<=l) edges[i].cap=1;
        else edges[i].cap=0;
}

int main() 
{
    freopen("poj2455.txt","r",stdin);
    freopen("poj2455ans.txt","w",stdout);
    index=0;
    long l,r,n,p,t,a,b,minl,maxl,mid,i,ncap;
    while(scanf("%ld%ld%ld",&n,&p,&t)!=EOF)
    {
        source=1;
        target=n;
        pointnum=n;
	minl=INF;
	maxl=0;
        memset(first,-1,sizeof(first));
        for(i=0;i<p;++i)
        {
            scanf("%ld%ld%ld",&a,&b,&l);
            edges[index].next=first[a];
	    edges[index].trg=b;
	    edges[index].len=l;
	    edges[index].pair=index+1;
	    first[a]=index++;
            edges[index].next=first[b];
	    edges[index].trg=a;
	    edges[index].len=l;
	    edges[index].pair=index-1;
	    first[b]=index++;	
            if (minl>l) minl=l;
            if (maxl<l) maxl=l;			
        }
	l=minl;r=maxl;
	while (l<r)
	{
	    mid=(l+r)/2;
	    BuildMap(mid);
	    ncap=SAP();
	    if (ncap>=t) r=mid;
            else l=mid+1;			
	}
        printf("%ld\n",l);
    }
    return 0;
}