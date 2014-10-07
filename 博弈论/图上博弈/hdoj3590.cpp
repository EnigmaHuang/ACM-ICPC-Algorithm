#include<stdio.h>
#include<string.h>
#include<vector>

using namespace std;

vector <int> edge[100005];

int GetSG(int u,int pre)
{
    int res=0,esize,i;
    esize=edge[u].size();
    for (i=0;i<esize;i++)
        if (edge[u][i]!=pre)
            res^=(1+GetSG(edge[u][i],u));
    return res;
}

int main()
{
    int t,n,res,cnt,i,u,v,tmp;
    freopen("hdoj3590.txt","r",stdin);
    freopen("hdoj3590ans.txt","w",stdout);
    while (scanf("%d",&t)!=EOF)
    {
        res=0;
        cnt=0;
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
            tmp=GetSG(1,-1);
            if (tmp>1) cnt++;
            res^=tmp;
        }
        if (cnt==0)
        {
            if (res) printf("QQ\n");
            else printf("PP\n");
        }
        else
        {
            if (res==0) printf("QQ\n");
            else printf("PP\n");
        }
    }
    return 0;
}

