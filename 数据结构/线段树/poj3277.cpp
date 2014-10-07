#include <stdio.h>
#include <algorithm>
#define MaxN 40005

using namespace std;

struct TNode
{
    int l,r,h;
}node[8*MaxN];  //这里注意，因为最多有2*MaxN个点，所以需要4*2*MaxN个节点才保险

int segpos[2*MaxN],height[MaxN],lpos[MaxN],rpos[MaxN];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].h=0;
    if (left+1==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid,right,u*2+1);
}

void SegmentUpdate(int left,int right,int &i,int u)
{
    int mid;
    if (segpos[node[u].l]==left && segpos[node[u].r]==right) //找到与目标长度相等的
    {
        if (node[u].h<height[i]) node[u].h=height[i];  //比已有的高度高，覆盖之
        return;
    }
    mid=segpos[(node[u].l+node[u].r)/2];
    if (right<=mid) SegmentUpdate(left,right,i,u*2);
    else if (left>=mid) SegmentUpdate(left,right,i,u*2+1);
    else
    {
        SegmentUpdate(left,mid,i,u*2);
        SegmentUpdate(mid,right,i,u*2+1);
    }
}

long long count(int h,int u)    //算每个子结点的面积并
{
    long long a,b;
    //延迟覆盖操作，如果父节点更高，
    //则子节点跟随父节点的高度
    if (node[u].h<h) node[u].h=h; 
    //区间中间没有分隔点了，直接返回面积
    if (node[u].l+1==node[u].r) return 1LL*(segpos[node[u].r]-segpos[node[u].l] )*node[u].h;
    a=count(node[u].h,u*2);
    b=count(node[u].h,u*2+1);
    return a+b;
}

int main()
{
    int n,m,a,b,i,k;
    long long ans;
    freopen("poj3277.txt","r",stdin);
    freopen("poj3277ans-2.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        k=0;
        for (i=1;i<=n;i++)  //离散化
        {
            scanf("%d%d%d",&lpos[i],&rpos[i],&height[i]);
            segpos[++k]=lpos[i];
            segpos[++k]=rpos[i];
        }
        //unique要求先排序
        sort(segpos+1,segpos+k+1);
        //然后会将不同的集中到前面，返回最后一个不同元素后一位的指针
        //因此减去队首元素的指针再-1就得到不同的元素的个数
        m=unique(segpos+1,segpos+k+1)-segpos-1;

        BuildTree(1,m,1);
        for (i=1;i<=n;i++) SegmentUpdate(lpos[i],rpos[i],i,1);
        ans=count(0,1);
        printf("%lld\n",ans);
    }
  return 0;
}
