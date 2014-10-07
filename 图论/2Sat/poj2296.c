#include<string.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h> 
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 205 
#define MaxE 40050 

/*----------Tarjan Template Start----------*/

struct TEdge
{
    int v,next;
}Edge[MaxE];
int head[MaxN],index;

int dfn[MaxN];  //dfn[u]:遍历到u点的时间; 
int low[MaxN];  //low[u]:u或u的子树能够追溯到的最早的栈中节点的次序号
int grp[MaxN];  //grp[u]:u属于的连通分量的编号
int vis[MaxN];  //v是否在栈中
int stack[MaxN],top,scc,cnt;

void AddEdge(int u,int v)
{
    index++;
    Edge[index].v=v;
    Edge[index].next=head[u];
    head[u]=index;
}

void Tarjan(int u)
{
    int v,i;
    dfn[u]=low[u]=++cnt;//开始时dfn[u]==low[u]
    stack[top++]=u;     //当前点进栈
    vis[u]=1;
    for (i=head[u];i!=-1;i=Edge[i].next)
    {
        v=Edge[i].v;
        if (dfn[v]==0) //如果v点还未遍历
        {
            Tarjan(v); //向下遍历
            low[u]=min(low[u],low[v]) //确保low[u]最小
        }
        else if (vis[v] && low[u]>dfn[v]) low[u] = dfn[v];
        //v在栈中，修改low[u]          
    }
    if (dfn[u]==low[u])     //u为该强连通分量中遍历所成树的根
    {
        scc++;
        do
        {
            v=stack[--top]; //栈中所有到u的点都属于该强连通分量，退栈
            vis[v]=0;
            grp[v]=scc;
        } while (u!=v);
    }
}

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void Solve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(grp,-1,sizeof(grp));
    for (u=1;u<=NodeNum;u++) if (dfn[u]==0) Tarjan(u);
}

/*----------Tarjan Template Over----------*/

struct TPos
{
    int x,y;
}p[MaxN];

int n;

void BuildMap(int r)
{
    int i,j;
    InitEdge();
    for (i=1;i<n;i++)
        for (j=i+1;j<=n;j++)
        {
       	    if (abs(p[i].x-p[j].x)>=r)   continue;
       	    if (abs(p[i].y-p[j].y)>=2*r) continue;
       	    if (abs(p[i].y-p[j].y)<r)
       	    {
       	        if (p[i].y>p[j].y)
       	        {
       	            AddEdge(i,j+n);
       	            AddEdge(j+n,i);
       	            AddEdge(i+n,i);
       	            AddEdge(j,j+n);
       	        }
       	        if (p[i].y<p[j].y)
       	        {
       	            AddEdge(j,i+n);
       	            AddEdge(i+n,j);
       	            AddEdge(j+n,j);
       	            AddEdge(i,i+n);
       	        }
       	        if (p[i].y==p[j].y)
       	        {
       	            AddEdge(i,j+n);
       	            AddEdge(i+n,j);
       	            AddEdge(j,i+n);
       	            AddEdge(j+n,i);
       	        }
       	    }
       	    else
       	    {
       	        if (p[i].y>p[j].y)
       	        {
       	            AddEdge(i+n,j+n);
       	            AddEdge(j,i);
                }
       	        if (p[i].y<p[j].y)
       	        {
       	            AddEdge(j+n,i+n);
       	            AddEdge(i,j);
                }
       	    }
        }
} 

int SATJudge(int nodenum)
{
    int i;
    Solve(nodenum);
    for (i=1;i<=n;i++) if (grp[i]==grp[i+n]) return 0;
    return 1;
}

int main()
{
    int i,t,mid,ans,l,r;
    freopen("poj2296.txt","r",stdin);
    freopen("poj2296ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y);
        l=0;
        r=20000;
        while (l<r)
        {
       	    mid=(l+r)/2;
       	    BuildMap(mid);
       	    if (SATJudge(2*n))
       	    {
                l=mid+1;
                ans=mid;
       	    }
       	    else r=mid;
        }
        printf("%d\n",ans);
    }
    return 0;
} 
