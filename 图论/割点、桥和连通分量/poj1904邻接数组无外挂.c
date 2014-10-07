#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (a<b)?a:b;
#define max(a,b) (a>b)?a:b;

#define MaxN 4005
#define MaxE 210000

/*----------Tarjan Template Start----------*/

int dfn[MaxN];  //dfn[u]:遍历到u点的时间; 
int low[MaxN];  //low[u]:u或u的子树能够追溯到的最早的栈中节点的次序号
int grp[MaxN];  //grp[u]:u属于的连通分量的编号
int vis[MaxN];  //v是否在栈中

int map[MaxN][MaxN];  //边标记，用空间换时间吧…… 

int stack[MaxN],top,scc,cnt,n;

void Tarjan(int u)
{
    int v,i;
    dfn[u]=low[u]=++cnt;//开始时dfn[u]==low[u]
    stack[top++]=u;     //当前点进栈
    vis[u]=1;
    for (v=1;v<=2*n;v++)
    {
        if (!map[u][v]) continue;
        if (!dfn[v]) //如果v点还未遍历
        {
            Tarjan(v); //向下遍历
            low[u]=min(low[u],low[v]) //确保low[u]最小
        }
        else if (vis[v]) low[u]=min(low[u],dfn[v]);
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

void TarjanSolve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(low,0,sizeof(low));
    for (u=1;u<=NodeNum;u++) if (!dfn[u]) Tarjan(u);
}

/*----------Tarjan Template Over----------*/

int ans[2002],pos;

int main()
{
    int i,num,u,v,j;
    freopen("poj1904.txt","r",stdin);
    freopen("poj1904ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        memset(map,0,sizeof(map));
        for (u=1;u<=n;u++)
        {
            scanf("%d",&num);
            for (i=1;i<=num;i++)
            {
                scanf("%d",&v);
                map[u][v+n]=1;
            }
        }
        for (u=1;u<=n;u++)
        {
            scanf("%d",&v);
            map[v+n][u]=1;
        }
        TarjanSolve(2*n);
        for (i=1;i<=n;i++)
        {
            pos=0;
            for (j=n+1;j<=2*n;j++) 
            if (map[i][j] && grp[i]==grp[j]) ans[++pos]=j-n; //男爱女，且在同一联通分量（环）内即可 
            printf("%d",pos);
            for (j=1;j<=pos;j++) printf(" %d",ans[j]);
            printf("\n");    
        }
    }
}
