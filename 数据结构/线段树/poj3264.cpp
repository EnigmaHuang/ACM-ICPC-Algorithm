#include<stdio.h>
#include<string.h>

#define MaxN 50005
#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)

struct TNode
{
    int l,r;
    int min,max;
}node[MaxN*3];

int a[MaxN];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    if (left==right)
    {
        node[u].min=node[u].max=a[left];
        return;
    }
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
    node[u].min=Min(node[u*2].min,node[u*2+1].min);
    node[u].max=Max(node[u*2].max,node[u*2+1].max);
}

void SegmentQuery(int left,int right,int u,int &min,int &max)
{
    int mid,max1,max2,min1,min2;
    if (node[u].l==left && node[u].r==right)
    {
        min=node[u].min;
        max=node[u].max;
        return;
    }
    mid=(node[u].l+node[u].r)/2;
    if (mid>=right) SegmentQuery(left,right,u*2,min,max);
    else if (mid<left) SegmentQuery(left,right,u*2+1,min,max);
    else
    {
        SegmentQuery(left,mid,u*2,min1,max1);
        SegmentQuery(mid+1,right,u*2+1,min2,max2);
        min=Min(min1,min2);
        max=Max(max1,max2);
    }
}

int main()
{
    int n,q,i,l,r,min,max;
    freopen("poj3264.txt","r",stdin);
    freopen("poj3264ans.txt","w",stdout);
    while (scanf("%d%d",&n,&q)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&a[i]);
        BuildTree(1,n,1);
        for (i=1;i<=q;i++)
        {
            scanf("%d%d",&l,&r);
            SegmentQuery(l,r,1,min,max);
            printf("%d\n",max-min);
        }
    }
    return 0;
}
