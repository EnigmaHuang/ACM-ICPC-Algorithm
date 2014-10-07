#include<stdio.h>
#include<string.h>
#include<vector>

using namespace std;

vector <int> edge[1005],roots;

int GetSG(int u,int pre)
{
    int i,res=0,esize;
    esize=edge[u].size();
    for (i=0;i<esize;i++)
        if (edge[u][i]!=pre)
            res^=(1+GetSG(edge[u][i],u));
    return res;
}

int main()
{
    int t,n,i,u,v,res,rsize;
    freopen("hdoj3197.txt","r",stdin);
    freopen("hdoj3197ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<=n;i++) edge[i].clear();
        roots.clear();
        for (v=0;v<n;v++)
        {
            scanf("%d",&u);
            if (u==-1) roots.push_back(v);
            else
            {
                edge[u].push_back(v);
                edge[v].push_back(u);
            }
        }
        rsize=roots.size();
        res=0;
        for (i=0;i<rsize;i++) res^=GetSG(roots[i],-1);
        if (res) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
