#include<stdio.h>
#include<string.h>
#define MaxN 201

int SG[MaxN][MaxN];

int GetSG(int n,int m)
{
    int i,vis[MaxN];
    if (SG[n][m]!=-1) return SG[n][m];
    memset(vis,0,sizeof(vis));
    for (i=2;i<=n-i;i++) vis[GetSG(i,m)^GetSG(n-i,m)]=1;
    for (i=2;i<=m-i;i++) vis[GetSG(n,i)^GetSG(n,m-i)]=1;
    for (i=0;i<MaxN;i++) if (vis[i]==0)
    {
        SG[n][m]=i;
        return SG[n][m];
    }
}

int main()
{
    int n,m;
    memset(SG,-1,sizeof(SG));
    while (scanf("%d%d",&n,&m)!=EOF)
        if (GetSG(n,m)) printf("WIN\n"); else printf("LOSE\n");
    return 0;
}
