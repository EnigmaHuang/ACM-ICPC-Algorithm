#include<stdio.h>

int a[101];

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
    int n,i,j,res,k,cnt;
    freopen("hdoj3537.txt","r",stdin);
    freopen("hdoj3537ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        if (n==0)
        {
            printf("Yes\n");
            continue;
        }
        for (i=0;i<n;i++) scanf("%d",&a[i]);
        QSort(0,n-1);
        res=0;
        cnt=1;
        for (i=1;i<n;i++) if (a[i]!=a[cnt-1]) a[cnt++]=a[i];
        for (i=0;i<cnt;i++)
        {
            j=a[i];
            k=0;
            while (j)
            {
                if (j&1) k++;
                j>>=1;
            }
            if (k%2==0) res^=2*a[i]+1; //odious数,SG值为2x+1 
            else res^=2*a[i];          //evil数，SG值为2x 
        }
        if (res) printf("No\n"); else printf("Yes\n"); 
    }
    return 0;
}
