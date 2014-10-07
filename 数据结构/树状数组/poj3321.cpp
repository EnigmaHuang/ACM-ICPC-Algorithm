#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxN 100005

int tree[MaxN];

void add(int x,int value)
{
    int i;
    for (i=x;i<=MaxN;i+=lowbit(i)) tree[i]+=value;
}

int sum(int x)
{
    int i,res=0;
    for (i=x;i;i-=lowbit(i)) res+=tree[i];
    return res;
}

struct TEdge
{
    int v,next;
}edge[2*MaxN];

int index,head[MaxN];
int low[MaxN],high[MaxN],vis[MaxN],depth;

void DFS(int u)
{
    int i;
    depth++;      
    low[u]=depth;   //第一次到达的深度
    vis[u]=1;
    for (i=head[u];i;i=edge[i].next) if (!vis[edge[i].v]) DFS(edge[i].v);
    high[u]=depth;  //搜索完毕出去以后的深度
}

int pick[MaxN];

int main()
{
    int i,u,v,n,m,ans;
    char s[5];
    freopen("poj3321.txt","r",stdin);
    freopen("poj3321ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        index=1;
        memset(head,0,sizeof(head));
        for (i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            edge[index].v=v;
            edge[index].next=head[u];
            head[u]=index++;
        }
        for (i=1;i<=n;i++) add(i,1);
        memset(pick,0,sizeof(pick));
        memset(vis,0,sizeof(vis));
        depth=0;
        DFS(1);
        scanf("%d",&m);
        while (m--)
        {
            scanf("%s%d",s,&u);
            if (s[0]=='C')
            {
                if (pick[u])
                {
                    add(low[u],1);
                    pick[u]=0;
                }
                else
                {
                    add(low[u],-1);
                    pick[u]=1;
                }
            }
            else
            {
                ans=sum(high[u])-sum(low[u]-1);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
