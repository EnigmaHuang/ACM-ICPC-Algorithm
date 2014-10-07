#include <stdio.h>
#define MaxN 50010 

int n,len[MaxN];
//存储的是最大值和最小值的下标 
int minl[MaxN][20],maxl[MaxN][20];


int Min(int l,int r)
{
    if (len[l]<len[r]) return l; return r;
}

int Max(int l,int r)
{
    if (len[l]>len[r]) return l; return r;
}

int TMax(int a,int b)
{
    if (a>b) return a; return b;
}

void MakeRMQ()
{
    int i,j;
    for (i=1;i<=n;i++) minl[i][0]=maxl[i][0]=i;  //数组记录的是下标，注意 
    for (j=1;(1<<j)<=n;j++)
    {
        for (i=1;i+(1<<j)-1<=n;i++)
        {
            minl[i][j]=Min(minl[i][j-1],minl[i+(1<<(j-1))][j-1]);
            maxl[i][j]=Max(maxl[i][j-1],maxl[i+(1<<(j-1))][j-1]);
        }
    }
}

int MinRMQ(int l,int r)
{
    int k=0;
    while ( (1<<(k+1)) <= r-l+1 ) k++;
    return Min(minl[l][k], minl[r+1-(1<<k)][k]);
}

int MaxRMQ(int l, int r)
{
    int k=0;
    while ( (1<<(k+1)) <= r-l+1 ) k++;
    return Max(maxl[l][k], maxl[r+1-(1<<k)][k]);
}

int BinSearch(int x, int l, int r)
{
    int m; 
    while (l<=r)
    {
        if (l==r) return l;
        m=(l+r)>>1;
        if (len[x]<len[MinRMQ(l,m)]) l=m+1;
        else r=m;
    }
}

void Solve()
{
    int ans=0,i,r,k;
    for (i=1;i+ans<n;i++)
    {
        r=BinSearch(i,i+1,n);
        k=MaxRMQ(i,r);
        if (len[k]>len[i]) ans=TMax(ans,k-i);
    }
    if (ans==0) printf("-1\n");
    else printf("%d\n",ans);
}

int main()
{
    int i; 
    freopen("poj2452.txt","r",stdin);
    freopen("poj2452ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&len[i]);
        MakeRMQ();
        Solve();
    }
    return 0;
}
