#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MaxN 505
#define MaxE 505*505

/*---------------Hungary Template Start---------------*/

struct TEdge
{
    int u,v,next;
}edge[MaxE];
int head[MaxN],index;
int link[MaxN],vis[MaxN],pointnum;

void AddEdge(int src,int trg)
{
    edge[index].u=src;
    edge[index].v=trg;
    edge[index].next=head[src];
    head[src]=index++;
}

void InitMap(int pn)
{
    pointnum=pn;
    index=0;
    memset(head,-1,sizeof(head));
}

int Find(int u)  
{  
    int i,v;
    for(i=head[u];i!=-1;i=edge[i].next)  
    {
        v=edge[i].v;
        if (!vis[v])
        {
       	    vis[v]=1;
       	    if (link[v]==-1 || Find(link[v])) //Y部图的点还没被匹配，或者已经被匹配但是可以重新匹配
            {
                link[v]=u;
                return 1;
            } 
        }
    }
   return 0;
} 

int Hungary()  
{  
    int i,res; 
    res=0; 
    memset(link,-1,sizeof(link));
    for(i=1;i<=pointnum;i++)
    {  
        memset(vis,0,sizeof(vis));  
        if (Find(i)) res++;  //对每一个点都寻找一次匹配 
    }
    return res;
}

/*---------------Hungary Template Over---------------*/

int n; 

int MHTDist(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2)+abs(y1-y2);
} 

struct TPath
{
    int x1,x2,y1,y2;
    int st,ed;
}path[MaxN];

int main()
{
    int i,j,testcase,h,m;
    freopen("poj2060.txt","r",stdin);
    freopen("poj2060ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d",&n);
        InitMap(n);
        for (i=1;i<=n;i++)
        {
            scanf("%d:%d",&h,&m);
            scanf("%d%d%d%d",&path[i].x1,&path[i].y1,&path[i].x2,&path[i].y2);
            path[i].st=h*60+m;
            path[i].ed=path[i].st+MHTDist(path[i].x1,path[i].y1,path[i].x2,path[i].y2);
            for (j=1;j<=i-1;j++)
            {
                if (path[i].st>=path[j].ed+MHTDist(path[i].x1,path[i].y1,path[j].x2,path[j].y2)+1)
                {
                    AddEdge(i,j);
                }        
            }
	}
	printf("%d\n",n-Hungary());
    }
    return 0;
}
