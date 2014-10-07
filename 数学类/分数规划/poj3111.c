#include <stdio.h>
#define eps  0.00001
#define MaxN 100005

struct TJewel
{
    int v,w,index;
    double key;
}jewel[MaxN];

int n,k;

void QSort(int l,int r)
{
    int i,j;
    double mid;
    struct TJewel swap;
    i=l;j=r;
    mid=jewel[(l+r)/2].key;
    while (i<=j)
    {
        while (jewel[i].key>mid) i++;
        while (jewel[j].key<mid) j--;
        if (i<=j)
        {
       	    swap=jewel[i];
       	    jewel[i]=jewel[j];
       	    jewel[j]=swap;
       	    i++;j--;
        }
    }
    if (l<j) QSort(l,j);
    if (i<r) QSort(i,r);
}

int Check(double mid)
{
    int i;
    double sum=0.0;
    for (i=1;i<=n;i++) jewel[i].key=jewel[i].v-mid*jewel[i].w;
    QSort(1,n);
    for (i=1;i<=k;i++) sum+=jewel[i].key;
    if (sum>=0.0) return 1; else return 0;
}

int main()
{
    int i;
    double l,r,mid;
    freopen("poj3111.txt","r",stdin);
    freopen("poj3111ans.txt","w",stdout);
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        l=r=0.0;
        for (i=1;i<=n;i++) 
        {
            scanf("%d%d",&jewel[i].v,&jewel[i].w);
            jewel[i].index=i;
            r+=jewel[i].v;
        }
        while (r-l>eps)
        {
       	    mid=(l+r)/2;
       	    if (Check(mid)) l=mid; else r=mid;
        }
        for (i=1;i<k;i++) printf("%d ",jewel[i].index);
        printf("%d\n",jewel[k].index);
    }
    return 0;
}
