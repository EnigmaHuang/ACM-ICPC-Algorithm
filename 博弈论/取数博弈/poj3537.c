#include<stdio.h>
#include<string.h>

#define MaxN 2005

int SG[MaxN];

int GetSG(int n)
{
    int hash[MaxN],i;
    if (SG[n]!=-1) return SG[n];
    if (n<=0) return 0;
    memset(hash,0,sizeof(hash));
    for (i=1;i<=n/2+1;i++) hash[GetSG(i-3)^GetSG(n-i-2)]=1;
    for (i=0;i<MaxN;i++) if (hash[i]==0)
    {
        SG[n]=i;
        return i;
    }
}

int main()
{
    int n,ans;
    memset(SG,-1,sizeof(SG));
    while (scanf("%d",&n)!=EOF)
    {
        ans=GetSG(n);
        if (ans) printf("1\n"); else printf("2\n");
    }
    return 0;
}
