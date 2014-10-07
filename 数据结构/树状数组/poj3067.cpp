#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxN 1005

struct TEdge
{
    int u,v;
};

int cmp(TEdge &a,TEdge &b)
{
    if (a.u==b.u) return (a.v>b.v);
    else return (a.u>b.u);
}

void QSort(TEdge p[],int l,int r)
{
    int i=l,j=r;
    TEdge swap,mid=p[(l+r)/2];
    while (i<=j)
    {
        while (cmp(p[i],mid)) i++;
        while (cmp(mid,p[j])) j--;
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

TEdge e[MaxN*MaxN];
int tree[MaxN];
int n,m,k;

void add(int x,int value)
{
    int i;
    for (i=x;i<=MaxN;i+=lowbit(i)) tree[i]+=value;
}

int sum(int x)
{
    int i,res=0;
    for (i=x;i;i-=lowbit(i)) res+=tree[i];
    return res;
}

int main()
{
    int t,i,j;
    long long ans;
    freopen("poj3067.txt","r",stdin);
    freopen("poj3067ans.txt","w",stdout);
    scanf("%d",&t);
    for (j=1;j<=t;j++)
    {
        memset(tree,0,sizeof(tree));
        scanf("%d%d%d",&n,&m,&k);
        for (i=0;i<k;i++) scanf("%d%d",&e[i].u,&e[i].v);
        QSort(e,0,k-1);
        ans=0;
        for (i=0;i<k;i++)
        {
            ans+=(long long)sum(e[i].v-1);
            add(e[i].v,1);
        }
        printf("Test case %d: %lld\n",j,ans);
    }
    return 0;
}
