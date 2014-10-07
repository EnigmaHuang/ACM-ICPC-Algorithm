#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define eps  0.000001
#define MaxN 1005

struct TFrac
{
    int c,v;
    double d;
}s[MaxN];

int n,k;

void QSort(int l,int r)
{
    int i=l,j=r;
    double mid=s[(l+r)/2].d;
    struct TFrac swap;
    while (i<=j)
    {
        while (s[i].d>mid) i++;
        while (s[j].d<mid) j--;
        if (i<=j)
        {
       	    swap=s[i];
       	    s[i]=s[j];
       	    s[j]=swap;
       	    i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

double Work()
{
    double l,r,mid,sum;
    int i; 
    l=0;mid=0;
    for (i=1;i<=n;i++)  
    {
        s[i].d=(double)s[i].v/s[i].c;
        if (s[i].d>mid) mid=s[i].d;
    }
    r=mid;
    while (r-l>eps)
    {
        sum=0;
        mid=(l+r)/2;
        for (i=1;i<=n;i++) s[i].d=s[i].v-mid*s[i].c;
        QSort(1,n);
        for (i=1;i<=n-k;i++) sum+=s[i].v-mid*s[i].c;
        if (sum>0) l=mid; else r=mid;
    }
    return mid*100;
}

int main()
{
    int i;
    double ans;
    freopen("poj2976.txt","r",stdin);
    freopen("poj2976ans.txt","w",stdout);
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        if (n==0 && k==0) break;
        for (i=1;i<=n;i++) scanf("%d",&s[i].v);
        for (i=1;i<=n;i++) scanf("%d",&s[i].c);
        ans=Work();
        printf("%.0f\n",ans);
    }
    return 0;
}
