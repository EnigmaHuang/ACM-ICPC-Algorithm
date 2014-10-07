#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define min(a,b) (a<b)?a:b;
#define max(a,b) (a>b)?a:b;
#define MaxN 4005
#define MaxE 205000

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

void AddEdge(int u, int v)
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
        if (!dfn[v]) //如果v点还未遍历
        {
            Tarjan(v); //向下遍历
            low[u]=min(low[u],low[v]) //确保low[u]最小
        }
        else if (vis[v] && low[u]>dfn[v]) low[u]=dfn[v];
        //v在栈中，修改low[u]          
    }
    if (dfn[u]==low[u])     //u为该强连通分量中遍历所成树的根
    {
        scc++;
        while (1)
        {
            v=stack[--top]; //栈中所有到u的点都属于该强连通分量，退栈
            vis[v]=0;
            grp[v]=scc;
            if (u==v) break;
        }
    }
}

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void TarjanSolve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(low,0,sizeof(low));
    for (u=1;u<=NodeNum;u++) if (dfn[u]==0) Tarjan(u);
}

/*----------Tarjan Template Over----------*/

int n;
int ans[2002],pos;

void QSort(int l,int r)
{
    int i,j,mid,swap;
    i=l;j=r; 
    mid=ans[(l+r)/2];
    while (i<=j)
    {
        while (ans[i]<mid) i++;
        while (ans[j]>mid) j--;
        if (i<=j)
        {
       	    swap=ans[i];
       	    ans[i]=ans[j];
       	    ans[j]=swap;
       	    i++;j--;
        }
    }
    if (l<j) QSort(l,j);
    if (i<r) QSort(i,r);
}

int main()
{
    int i,num,u,v,j;
    freopen("poj1904.txt","r",stdin);
    freopen("poj1904ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitEdge();
        for (u=1;u<=n;u++)
        {
            scanf("%d",&num);
            for (i=1;i<=num;i++)
            {
                scanf("%d",&v);
		AddEdge(u,v+n);
            }
        }
        for (u=1;u<=n;u++)
        {
            scanf("%d",&v);
            AddEdge(v+n,u);
        }
        TarjanSolve(2*n);
        for (i=1;i<=n;i++)
        {
            pos=0;
            for (j=head[i];j!=-1;j=Edge[j].next)
            {
                v=Edge[j].v;
                if (grp[i]==grp[v]) ans[++pos]=v-n;
            }
            printf("%d",pos);
            QSort(1,pos); 
            for (j=1;j<=pos;j++) printf(" %d",ans[j]);
            printf("\n");    
        }
    }
}
