#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxN 100005

struct TCow
{
    int id,s,e;
}cow[MaxN];

int tree[MaxN],ans[MaxN];

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

inline int cmp(TCow &a,TCow &b)  //e降序，s升序，确保在前面的牛更牛逼
{
    if (a.e==b.e) return (a.s<b.s);
    else return (a.e>b.e);
}

void QSort(TCow p[],int l,int r)
{
    int i=l,j=r;
    TCow swap,mid=p[(l+r)/2];
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

int main()
{
    int n,i,s,e,same;
    TCow pre;
    freopen("poj2481.txt","r",stdin);
    freopen("poj2481ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        memset(tree,0,sizeof(tree));
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&s,&e);
            s++;e++;
            cow[i].s=s;
            cow[i].e=e;
            cow[i].id=i;
        }
        QSort(cow,0,n-1);
        pre.s=pre.e=-1;
        for (i=0;i<n;i++)
        {
            if (cow[i].s==pre.s && cow[i].e==pre.e) same++;
            else
            {
                same=0;
                pre.s=cow[i].s;
                pre.e=cow[i].e;
            }
            ans[cow[i].id]=sum(cow[i].s)-same;
            add(cow[i].s,1);
        }
        for (i=0;i<n;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
