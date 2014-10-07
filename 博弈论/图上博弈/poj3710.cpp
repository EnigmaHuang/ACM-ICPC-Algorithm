#include<stdio.h>
#include<string.h>
#include<vector>

using namespace std;

#define MaxN 105
#define min(a,b) (a)<(b)?(a):(b)

vector <int> edge[MaxN]; 
int  map[MaxN][MaxN];     //边数，用于直接判重
int  low[MaxN],dfn[MaxN];
int  s[MaxN],top;
bool instack[MaxN];
bool used[MaxN];          //Tarjan找环后，把不需要的点标记掉

void Tarjan(int u,int pre,int depth)
{
    int i,v,esize,cnt;
    low[u]=dfn[u]=depth;
    s[top++]=u;
    instack[u]=1;
    esize=edge[u].size();
    for (i=0;i<esize;i++)
    {
        v=edge[u][i];
        if (v==pre && map[u][v]>1) //重边
        {   
            if (map[u][v]%2==0) used[u]=1;
            continue;
        }
        if (!dfn[v])
        {
            Tarjan(v,u,depth+1);
            low[u]=min(low[u],low[v]);
        }
        else if (v!=pre && instack[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u])
    {
        cnt=1;
        top--;
        while (s[top]!=u)
        {
            used[s[top--]]=1;
            cnt++;
        }
        //如果节点为奇数，则保留一个点，包括u，也就是两个点，保留一条边
        if (cnt && (cnt&1)) used[s[top+1]]=0;
    }
}

int GetSG(int u,int pre)
{
    int res=0,i,v,esize;
    esize=edge[u].size();
    for (i=0;i<esize;i++)
    {
        v=edge[u][i];
        if (!used[v] && v!=pre) res^=(1+GetSG(v,u));
    }
    return res;
}

int main()
{
    int k,n,m,i,res,u,v;
    freopen("poj3710.txt","r",stdin);
    freopen("poj3710ans.txt","w",stdout);
    while (scanf("%d",&k)!=EOF)
    {
        res=0;
        while (k--)
        {
            scanf("%d%d",&n,&m);
            for (i=1;i<=n;i++) edge[i].clear();
            memset(map,    0,sizeof(map));
            memset(low,    0,sizeof(low));
            memset(dfn,    0,sizeof(dfn));
            memset(instack,0,sizeof(instack));
            memset(used,   0,sizeof(used));
            top=0;
            while (m--)
            {
                scanf("%d%d",&u,&v);
                map[u][v]++;
                map[v][u]++;
                edge[u].push_back(v);
                edge[v].push_back(u);
            }
            Tarjan(1,0,1);
            res^=GetSG(1,0);
        }
        if (res) printf("Sally\n"); else printf("Harry\n");
    }
    return 0;
}
