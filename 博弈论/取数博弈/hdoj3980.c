#include<stdio.h>
#include<string.h>
#define MaxN 1005

int SG[MaxN],vis[MaxN];

int GetSG(int n,int m)
{
    int i,j;
    memset(SG,0,sizeof(SG));
    for (i=m;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        for (j=0;j+m<=i;j++) vis[SG[j]^SG[i-j-m]]=1;
        for (j=0;j<MaxN;j++) if (vis[j]==0)
        {
            SG[i]=j;
            break;
        }
    }
}

int main()
{
    int t,cases=1,n,m;
    freopen("hdoj3980.txt","r",stdin);
    freopen("hdoj3980ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        if (n<m)
        {
            printf("Case #%d: abcdxyzk\n",cases++);
            continue;
        }
        GetSG(n-m,m);
        if (SG[n-m]==0) printf("Case #%d: aekdycoin\n",cases++);
        else printf("Case #%d: abcdxyzk\n",cases++);
    }
    return 0;
}
