#include <stdio.h>
#include <string.h>

#define MaxN 205
#define inf 0x3f3f3f3f
#define min(a,b) (a)<(b)?(a):(b)

int id[1005];        //存各牛的顶点（离散化）
int map[MaxN][MaxN]; //存邻接矩阵 
int ans[MaxN][MaxN]; //存答案 
int tmp[MaxN][MaxN]; //临时用 

int n,t,s,e,pointnum;

void AddEdge(int u,int v,int w)
{
    if (id[u]==-1)
    {
        pointnum++;
        id[u]=pointnum;
    }
    if (id[v]==-1)
    {
        pointnum++;
        id[v]=pointnum;
    }
    if (map[id[u]][id[v]]>w) map[id[u]][id[v]]=map[id[v]][id[u]]=w;
}

void Floyd(int a[MaxN][MaxN],int b[MaxN][MaxN],int dest[MaxN][MaxN])
{
    int i,j,k;
    memset(tmp,inf,sizeof(tmp));
    for (k=1;k<=pointnum;k++)
        for (i=1;i<=pointnum;i++)
	    for (j=1;j<=pointnum;j++) 
	        tmp[i][j]=min(tmp[i][j],a[i][k]+b[k][j]);
    memcpy(dest,tmp,sizeof(tmp)); //将结果赋给dest 
}

int main()
{
    int i,u,v,w;
    freopen("poj3613.txt","r",stdin);
    freopen("poj3613ans.txt","w",stdout);
    while (scanf("%d%d%d%d",&n,&t,&s,&e)!=EOF)
    {
        memset(id,-1,sizeof(id));
        memset(map,inf,sizeof(map));
        memset(ans,inf,sizeof(ans));
        for (i=0;i<MaxN;i++) ans[i][i]=0;
        pointnum=0;
        for (i=1;i<=t;i++)
        {
       	    scanf("%d%d%d",&w,&u,&v);
       	    AddEdge(u,v,w);
        }
        while (n)
        {
       	    if (n&1) Floyd(ans,map,ans);
       	    n>>=1;
       	    Floyd(map,map,map);
        }
        printf("%d\n",ans[id[s]][id[e]]);
    }
} 
