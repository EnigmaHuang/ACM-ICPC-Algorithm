#include<string.h>
#include<stdio.h>
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 5005
#define MaxE 50005

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

struct TLine
{
    int s,e;
}line[MaxN];

int JudgeLine(int l1,int l2)
{
    int a,b,c,d;
    a=line[l1].s;
    b=line[l1].e;
    c=line[l2].s;
    d=line[l2].e;
    if (c<a && a<d && d<b) return 1;
    if (a<c && c<b && b<d) return 1;
    return 0;
}

int main()
{
    int n,m,i,j,flag;
    freopen("poj3207.txt","r",stdin);
    freopen("poj3207ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=m;i++) scanf("%d%d",&line[i].s,&line[i].e);
        InitEdge();
        for (i=1;i<m;i++)
            for (j=i+1;j<=m;j++) if (JudgeLine(i,j))
            {
                AddEdge(2*i+1,2*j);
                AddEdge(2*j+1,2*i);
                AddEdge(2*i,2*j+1);
                AddEdge(2*j,2*i+1);
            }
        Solve(2*m);
        flag=1;
        for (i=1;i<=m;i++) if (grp[i*2]==grp[i*2+1])
        {
       	    flag=0;
       	    break;
        }
        if (flag) printf("panda is telling the truth...\n");
        else printf("the evil panda is lying again\n");
    }
    return 0;
}
