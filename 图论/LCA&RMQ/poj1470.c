#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MaxN 1005

int cnt[MaxN];      //答案计数 

/*----------LCA Tarjan Template Start----------*/

struct TEdge
{
    int u,v,next;
}edge[MaxN];
int head[MaxN],index;

int q[MaxN][MaxN];  //查询矩阵 

int father[MaxN],vis[MaxN]; //各点的父节点，访问标记
int root,n;                 //根节点，点数

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
    edge[index].u=u;
    edge[index].v=v;
    edge[index].next=head[u];
    head[u]=index++;
}

int GetFather(int x)
{
    if (father[x]==x) return x;
    father[x]=GetFather(father[x]);
    return father[x];
}

void Union(int x,int y)
{
    int fx,fy;
    fx=GetFather(x);
    fy=GetFather(y);
    if (fx==fy) return; else father[y]=fx;
}

void DFS(int u)
{
    int i,fa;
    for (i=head[u];i!=-1;i=edge[i].next)
    {
        DFS(edge[i].v);
        Union(u,edge[i].v);
    }
    vis[u]=1;
    for (i=1;i<=n;i++) if (vis[i] && q[u][i]) 
    {
        fa=GetFather(i);
        cnt[fa]+=q[u][i];
        q[u][i]=q[i][u]=0;
    }
}

void InitLCATarjan()
{
    memset(vis,0,sizeof(vis));
}

void LCATarjan(int n)
{
    int i;
    for (i=1;i<=n;i++) 
    {
        if (!vis[i]) root=i;
        father[i]=i;
    }
    memset(vis,0,sizeof(vis));
    DFS(root);
}

/*----------LCA Tarjan Template Over----------*/

int main()
{
    int u,v,k,i,j,t;
    char c;
    freopen("poj1470.txt","r",stdin);
    freopen("poj1470ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitEdge();
        InitLCATarjan();
        for (i=1;i<=n;i++)
        {
            scanf("%d:(%d)",&u,&k);
            for (j=1;j<=k;j++)
            {
                scanf("%d",&v);
                AddEdge(u,v);
                vis[v]=1;
            }
        }
        scanf("%d",&t);
        memset(q,0,sizeof(q));
        memset(cnt,0,sizeof(cnt));
        for (i=1;i<=t;i++)
        {
            while (scanf("%c",&c) && c!='(');  
            scanf("%d%d",&u,&v);
            q[u][v]++;
            q[v][u]++;
            while (scanf("%c",&c) && c!=')'); 
        }
        LCATarjan(n);
        for (i=1;i<=n;i++) if (cnt[i]) printf("%d:%d\n",i,cnt[i]); 
    }
    return 0;
}
