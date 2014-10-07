#include<stdio.h>

int a[10001];

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
    int i,j,n,m,flag;
    freopen("poj2368.txt","r",stdin);
    freopen("poj2368ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        m=0;
        for (i=1;i*i<=n;i++) if (n%i==0)
        {
            a[m++]=i;
            a[m++]=n/i;
        }
        QSort(0,m-1);
        flag=0;
        for (i=0;i<m;i++) if (a[i]>2)
        {
            flag=1;
            printf("%d\n",a[i]-1);
            break;
        }
        if (!flag) printf("0\n");
    }
    return 0;
}
