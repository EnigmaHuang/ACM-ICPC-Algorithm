#include<stdio.h>
#include<string.h>
#include<vector>

#define MaxN 1005

using namespace std;

vector <int> edge[MaxN];
int SG[MaxN],n;

int GetSG(int n)
{
    int i,esize;
    bool vis[MaxN];
    if (SG[n]!=-1) return SG[n];
    if (edge[n].size()==0) return 0;  //出度为0，必败态
    memset(vis,0,sizeof(vis));
    esize=edge[n].size();
    for (i=0;i<esize;i++)
    {
        SG[edge[n][i]]=GetSG(edge[n][i]);
        vis[SG[edge[n][i]]]=1;
    }
    for (i=0;i<MaxN;i++) if (vis[i]==0) return i;
}

int main()
{
    int i,k,v,ans;
    freopen("poj2425.txt","r",stdin);
    freopen("poj2425ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        memset(SG,-1,sizeof(SG));
        for (i=0;i<n;i++)
        {
            edge[i].clear();
            scanf("%d",&k);
            while (k--)
            {
                scanf("%d",&v);
                edge[i].push_back(v);
            }
        }
        while (scanf("%d",&k) && k)
        {
            ans=0;
            while (k--)
            {
                scanf("%d",&v);
                if (SG[v]==-1) SG[v]=GetSG(v);
                ans^=SG[v];
            }
            if (ans) printf("WIN\n"); else printf("LOSE\n");
        }
    }
    return 0;
}
