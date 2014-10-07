#include<stdio.h>
#include<string.h>
#define MaxN 1001

int fibo[MaxN],SG[MaxN],vis[MaxN];

void GetFibo()
{\
    int i;
    fibo[1]=1;
    fibo[2]=2;
    for (i=3;fibo[i]<MaxN;i++) fibo[i]=fibo[i-2]+fibo[i-1];
}

void GetSG()
{
    int i,j;
    memset(SG,0,sizeof(SG));
    for (i=1;i<MaxN;i++)
    {
        memset(vis,0,sizeof(vis));
        for (j=1;fibo[j]<=i;j++) vis[SG[i-fibo[j]]]=1;
        for (j=0;j<MaxN;j++) if (!vis[j])
        {
            SG[i]=j;
            break;
        }
    }
}

int main()
{
    GetFibo();
    GetSG();
    int n,m,p;
    while (scanf("%d%d%d",&n,&m,&p)!=EOF)
    {
        if (n==0 && m==0 && p==0) break;
        if (SG[m]^SG[n]^SG[p]) printf("fibo\n");
        else printf("Nacci\n");
    }
    return 0;
}
