#include<stdio.h>
#include<string.h>

#define MaxN 1005

int SG[MaxN],cnt,a[MaxN];

int GetSG(int n)
{
    int vis[MaxN],i,j;
    if (SG[n]!=-1) return SG[n];
    memset(vis,0,sizeof(vis));
    for (i=0;i<cnt && a[i]<=n;i++)
        for (j=0;j<=(n-a[i]);j++)
        {
            if (SG[j]==-1) SG[j]=GetSG(j);
            if (SG[n-j-a[i]]==-1) SG[n-j-a[i]]=GetSG(n-j-a[i]);
            vis[SG[j]^SG[n-j-a[i]]]=1;
        }
    for (i=0;i<MaxN;i++) if (!vis[i]) return i;
}

void QSort(int l,int r)
{
    int i=l,j=r,mid,swap;
    mid=a[(l+r)/2];
    while (i<=j)
    {
        while (a[i]<mid) i++;
        while (a[j]>mid) j--;
        if (i<=j)
        {
            swap=a[i];
            a[i]=a[j];
            a[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int main()
{
    int i,j,n,q,k;
    freopen("hdoj2999.txt","r",stdin);
    freopen("hdoj2999ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%d",&a[i]);
        QSort(0,n-1);
        cnt=1;
        for (i=1;i<n;i++) if (a[i]!=a[cnt-1]) a[cnt++]=a[i];
        scanf("%d",&q);
        memset(SG,-1,sizeof(SG));
        while (q--)
        {
            scanf("%d",&k);
            if (SG[k]==-1) SG[k]=GetSG(k);
            if (SG[k]) printf("1\n"); else printf("2\n");
        }
    }
    return 0;
}
