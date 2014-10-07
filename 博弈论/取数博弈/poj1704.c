#include<stdio.h>
#define MaxN 1001

int a[MaxN],b[MaxN];

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
    int t,n,i,j,ans,x,y;
    freopen("poj1704.txt","r",stdin);
    freopen("poj1704ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++) scanf("%d",&a[i]);
        QSort(0,n-1);
        j=0;
        ans=0;
        for (i=n-1;i>0;i--,j++) b[j]=a[i]-a[i-1]-1;
        b[n-1]=a[0]-1;
        for (i=0;i<n;i+=2) ans^=b[i];
        if (ans) printf("Georgia will win\n");
        else printf("Bob will win\n");
    }
    return 0;
}
