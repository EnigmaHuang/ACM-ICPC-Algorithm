#include<string.h>
#include<stdio.h>
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 2005
#define MaxE 2000050

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

int main()
{
    int n,m,i,a,b,flag;
    freopen("poj3905.txt","r",stdin);
    freopen("poj3905ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
	    if (a>0 && b>0)
	    {
                AddEdge(2*a+1,2*b);
                AddEdge(2*b+1,2*a);
            }
            if (a>0 && b<0)
            {
                b=-b;
                AddEdge(2*a+1,2*b+1);
                AddEdge(2*b,2*a);
            }
            if (a<0 && b>0)
            {
                a=-a;
                AddEdge(2*b+1,2*a+1);
                AddEdge(2*a,2*b);
            }
            if (a<0 && b<0)
            {
                a=-a;
                b=-b;
                AddEdge(2*a,2*b+1);
                AddEdge(2*b,2*a+1);
            }
        } 
        Solve(2*n+1);
        flag=1;
        for (i=1;i<=n;i++) if (grp[2*i]==grp[2*i+1])
        {
       	    flag=0;
       	    break;
        }
        printf("%d\n",flag);
    }
    return 0;
}

