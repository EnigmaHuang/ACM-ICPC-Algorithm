#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxT 500005

struct data
{
    int id,w;
}num[MaxT];

int n,tree[MaxT];

void add(int x,int value)
{
    int i;
    for (i=x;i<=MaxT;i+=lowbit(i)) tree[i]+=value;
}

long long sum(int x)
{
    long long res=0;
    int i;
    for (i=x;i;i-=lowbit(i)) res+=tree[i];
    return res;
}

void QSort(data p[],int l,int r)
{
    int i=l,j=r,mid=p[(l+r)/2].w;
    data swap;
    while (i<=j)
    {
        while (p[i].w>mid) i++;
        while (p[j].w<mid) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

int main()
{
    int i;
    long long ans;
    freopen("poj2299.txt","r",stdin);
    freopen("poj2299ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++)
        {
            scanf("%d",&num[i].w);
            num[i].id=i+1;
        }
        memset(tree,0,sizeof(tree));
        QSort(num,0,n-1);
        ans=0;
        for (i=0;i<n;i++)
        {
            ans+=sum(num[i].id-1);
            add(num[i].id,1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
