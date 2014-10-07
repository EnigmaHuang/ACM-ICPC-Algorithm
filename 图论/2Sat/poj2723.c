#include<string.h>
#include<stdio.h>
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 5005
#define MaxE 13005

/*----------2SAT Judge Template Start----------*/
/*------点从0开始编号，一组两个点编号隔1-------*/

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

int TwoSAT(int n)
{
    int i;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    scc=top=cnt=0;
    for(i=0;i<2*n;i++) if(!dfn[i]) Tarjan(i);
    for(i=0;i<n;i++) if(grp[i*2]==grp[i*2+1]) return 0;
    return 1;
}

/*----------2SAT Judge Template Over----------*/

int n,m;

struct TConflict
{
    int x,y;
}a[MaxN],b[MaxN];

int main()
{
    int i,ans,low,high,mid;
    freopen("poj2723.txt","r",stdin);
    freopen("poj2723ans.txt","w",stdout);
    while(scanf("%d%d",&n,&m),n||m)
    {
        for(i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
        for(i=1;i<=m;i++) scanf("%d%d",&b[i].x,&b[i].y);
        low=0;high=m;
        while(low<=high)
        {
            mid=(low+high)/2;
            InitEdge();
            for(i=1;i<=n;i++) 
            {
                AddEdge(2*a[i].x,2*a[i].y+1);
                AddEdge(2*a[i].y,2*a[i].x+1);
            }
            for(i=1;i<=mid;i++)
            {
                AddEdge(2*b[i].x+1,2*b[i].y);
                AddEdge(2*b[i].y+1,2*b[i].x);
            }
            if(mid==0 || TwoSAT(n)) 
            {
                ans=mid;
                low=mid+1;
            }
            else high=mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
