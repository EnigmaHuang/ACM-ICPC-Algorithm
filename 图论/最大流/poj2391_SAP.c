#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXN 500 
#define MAXE 500*500*2   
#define INF 0x3f3f3f3f 

struct edge
{      
    int next,pair;    //同一起点下一条边的编号，反向边的编号
    int trg,cap;      //该边指向的点，该边的剩余容量，该边的流量         
}edges[MAXE];         //边集 
int first[MAXN];      //每一个点出发的边的第一条的编号
int source,target,index,pointnum; 

int f,p,cownum,filternum;
long long maxlen,minlen;

int f1[MAXN],f2[MAXN];

long long map[MAXN][MAXN]; 

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

void AddEdge(const int u,const int v,const int c)
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

void Floyd()
{
    int i,j,mid;
    for (mid=1;mid<=f;mid++)
        for (i=1;i<=f;i++)
            for (j=1;j<=f;j++)
            {
                if (map[i][mid]+map[mid][j]<map[i][j]) map[i][j]=map[i][mid]+map[mid][j]; 
                if (map[i][j]>maxlen && map[i][j]<0x3f3f3f3f3f3f3f3f) maxlen=map[i][j];
                if (map[i][j]<minlen) minlen=map[i][j]; 
            } 
} 

void ReadData()
{
    int i,j,cow,filter,x,y,l;
    memset(map,0x3f3f3f3f,sizeof(map));
    source=2*f+1;
    target=source+1;
    pointnum=target;
    cownum=filternum=0;
    maxlen=0;
    minlen=INF;
    
    for (i=1;i<=f;i++)
    {
        scanf("%d %d",&cow,&filter);
        cownum+=cow;
        filternum+=filter;
        f1[i]=cow;
        f2[i]=filter;
    }

    for (i=1;i<=f;i++) map[i][i]=0;
    for (i=1;i<=p;i++)
    {
        scanf("%d %d %d",&x,&y,&l);
        if (l<map[x][y]) map[x][y]=map[y][x]=l;
    }
    Floyd();
}

void BuildMap(long long mid)
{
	int i,j,ff;
	InitSAP();
	for (i=1;i<=f;i++) AddEdge(i,i+f,INF);
    for (i=1;i<=f;i++)
    {
    	AddEdge(source,i,f1[i]);
    	AddEdge(i+f,target,f2[i]);
    }
    for (i=1;i<=f;i++)
        for (j=1;j<=f;j++)
            if (map[i][j]<=mid) AddEdge(i,j+f,INF);
} 

long long Solve()
{
    long long l,r,mid;
    int hasans=0;
    int flow;
    if (cownum>filternum) return(-1); 
    l=minlen;
    r=maxlen;
    while (l<=r)
    {
        mid=(l+r)/2;
        BuildMap(mid);
        flow=SAP();
        if (flow>=cownum) 
        {
            r=mid;
            if (l==r) r--;  
            hasans=1;
	}
        else l=mid+1;
    }
    if (hasans) return(l);else return(-1);
}

int main()
{
    freopen("poj2391.txt","r",stdin);
    freopen("poj2391ans.txt","w",stdout);
    while (scanf("%d %d",&f,&p)!=EOF)
    {
        ReadData();
        printf("%lld\n",Solve());
    }
} 
