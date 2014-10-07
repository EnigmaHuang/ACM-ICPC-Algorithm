#include<stdio.h>
#include<string.h>
#include<vector>

using namespace std;

vector <int> edge[100005];

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
    int t,n,i,u,v;
    freopen("hdoj3094.txt","r",stdin);
    freopen("hdoj3094ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=1;i<=n;i++) edge[i].clear();
        for (i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        if (GetSG(1,0)) printf("Alice\n"); else printf("Bob\n");
    }
    return 0;
}
