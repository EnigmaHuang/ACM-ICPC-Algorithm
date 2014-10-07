#include<stdio.h>
#include<string.h>

int dp[25][10005],a[25],n;

int DP(int pid,int rest)
{
    int i;
    if (dp[pid][rest]!=-1) return dp[pid][rest];
    if (rest==0)
    {
        dp[pid][rest]=1;
        return 1;
    }
    dp[pid][rest]=0;
    for (i=1;i<=a[pid] && i<=rest;i++)
        if (!DP((pid+1)%(2*n),rest-i)) dp[pid][rest]=1;
    return dp[pid][rest];
}

int main()
{
    int i,s;
    freopen("poj2068.txt","r",stdin);
    freopen("poj2068ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        scanf("%d",&s);
        memset(dp,-1,sizeof(dp));
        for (i=0;i<2*n;i++) scanf("%d",&a[i]);
        printf("%d\n",DP(0,s));
    }
    return 0;
}
