#include<stdio.h>
/*
#include<string.h>

int SG[1000000];
int vis[10000];

int MakeSG()
{
    int i,j,res;
    SG[0]=0;
    SG[1]=1;
    for (i=2;i<=10000;i++)
    {
        memset(vis,0,sizeof(vis));
        for (j=0;j<i;j++)
            vis[SG[j]]=1;
        for (j=1;j<=i/2;j++)
        {
            res=SG[j]^SG[i-j];  //两堆的SG值等于其异或
            vis[res]=1;
        }
        for (j=0;j<10000;j++) if (!vis[j]) break;
        SG[i]=j;
        printf("SG[%d] = %d\n",i,SG[i]);
    }
}
*/

int main()
{
    int t,n,i,k,ans;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&k);
            if (k%4==1 || k%4==2) ans^=k;
            else if (k%4==0) ans^=(k-1);
            else ans^=(k+1);
        }
        if (ans) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}
