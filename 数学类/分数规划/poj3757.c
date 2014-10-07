#include <stdio.h>
#include <string.h>
#define eps  0.00001
#define MaxN 20005

struct TServer
{
    double speed,cost,w;
}s[MaxN];

int n,k;
double f;

void QSort(int l,int r)
{
    int i,j;
    double mid;
    struct TServer swap;
    i=l;j=r;
    mid=s[(l+r)/2].w;
    while (i<=j)
    {
        while (s[i].w<mid) i++;
        while (s[j].w>mid) j--;
        if (i<=j)
        {
       	    swap=s[i];
       	    s[i]=s[j];
       	    s[j]=swap;
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
    for (i=1;i<=n;i++) s[i].w=s[i].cost-mid*s[i].speed;
    QSort(1,n);
    for (i=1;i<=k;i++) sum+=s[i].w;
    if (sum>=0.0) return 1;else return 0;
}

int main()
{
    int i;
    double p,b,c,sums,sumc,l,r,mid,ans;
    freopen("poj3757.txt","r",stdin);
    freopen("poj3757ans.txt","w",stdout);
    while (scanf("%d%d%lf",&n,&k,&f)!=EOF)
    {
    	l=r=0.0;
    	for (i=1;i<=n;i++)
    	{
            scanf("%lf %lf %lf",&p,&b,&c);
            s[i].speed=1/(1/p+1/b);
            s[i].cost=c*s[i].speed;
            r+=s[i].cost;
    	}
        while (r-l>eps)
        {
       	    mid=(l+r)/2;
       	    if (Check(mid))
       	    {
       	    	l=mid;
       	    	sums=sumc=0.0;
       	    	for (i=1;i<=k;i++)
       	    	{
                    sums+=s[i].speed;
                    sumc+=s[i].cost;
       	    	}
       	    	ans=sumc/sums;
       	    }
       	    else r=mid;
        }
        printf("%.4f\n",ans*f);
    }
}
