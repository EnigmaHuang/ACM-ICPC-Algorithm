#include<stdio.h>
#define MaxN 5005

struct TNode
{
    int l,r,sum;  //sum表示此区间段现在已经有多少个数了
}node[MaxN];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].sum=0;  //一开始没有数字进入，全部为0
    if (left==right) return;
    mid=(node[u].l+node[u].r)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PointUpdate(int k,int u)
{
    int mid;
    node[u].sum++;
    if (node[u].l==node[u].r) return;
    mid=(node[u].l+node[u].r)/2;
    if (k<=mid) PointUpdate(k,u*2);
    else PointUpdate(k,u*2+1);
}

int SegmentQuery(int left,int right,int u)
{
    int mid;
    if (left==node[u].l && node[u].r==right) return node[u].sum;
    mid=(node[u].l+node[u].r)/2;
    if (right<=mid)    return SegmentQuery(left,right,u*2);
    else if (left>mid) return SegmentQuery(left,right,u*2+1);
    else return SegmentQuery(left,mid,u*2)+SegmentQuery(mid+1,right,u*2+1);
}

int val[MaxN];

int main()
{
    int n,i,sum,ans;
    freopen("hdoj1394.txt","r",stdin);
    freopen("hdoj1394ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        BuildTree(0,n-1,1);
        sum=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&val[i]);
            sum+=SegmentQuery(val[i],n-1,1);  //查询已经插入的数里有多少个在val[i]
            PointUpdate(val[i],1);            //到n-1之间，即为逆序数，并插入这个数
        }
        ans=sum;
        for (i=0;i<n;i++)
        {
            sum=sum-val[i]+(n-val[i]-1);
            if (sum<ans) ans=sum;
        }
        printf("%d\n",ans);
    }
    return 0;
}
