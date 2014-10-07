#include<stdio.h>
#include<string.h>

#define MaxN 1001
#define MaxE 10001

struct TEdge
{
    int v,next;
}edge[MaxE];

int head[MaxN],index;
int CowCnt[MaxN];
int CowSum[MaxN];
int flag[MaxN];

void DFS(int u,int cnt)
{
    int i,v;
    for (i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (flag[v]) continue;
        flag[v]=1;
        CowSum[v]+=cnt;
        DFS(v,cnt);
    }
}

int main()
{
    int k,n,m,i,pos,u,v,ans;
    freopen("poj3256.txt","r",stdin);
    freopen("poj3256ans.txt","w",stdout);
    while (scanf("%d%d%d",&k,&n,&m)!=EOF)
    {
        index=0;
        memset(head,-1,sizeof(head));
        for (i=0;i<k;i++)
        {
            scanf("%d",&pos);
            CowCnt[pos]++;
        }
        for (i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            edge[index].v=v;
            edge[index].next=head[u];
            head[u]=index++;
        }
        for (i=1;i<=n;i++) if (CowCnt[i]!=0)
        {
            memset(flag,0,sizeof(flag));
            CowSum[i]+=CowCnt[i];
            flag[i]=1;
            DFS(i,CowCnt[i]);
        }
        ans=0;
        for (i=1;i<=n;i++) if (CowSum[i]==k) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
