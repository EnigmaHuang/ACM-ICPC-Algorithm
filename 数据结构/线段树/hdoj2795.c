#include<stdio.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 200005

struct TNode
{
    int l,r,maxlen;
}node[MaxN*3];

int h,w,n,ans;

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].maxlen=w;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PointUpdate(int x,int u)
{
    if (node[u].maxlen<x)      //进入的区间无法满足，返回-1
    {
        ans=-1;
        return;
    }
    if (node[u].l==node[u].r)  //到叶节点，直接更新
    {
        node[u].maxlen-=x;
        ans=node[u].l;
        return;
    }
    //先更新左右两个子树
    if (node[u*2].maxlen>=x) PointUpdate(x,u*2);
    else if (node[u*2+1].maxlen>=x) PointUpdate(x,u*2+1);
    //然后更新当前的节点情况
    node[u].maxlen=Max(node[u*2].maxlen,node[u*2+1].maxlen);
}

int main()
{
    int i,k;
    freopen("hdoj2795.txt","r",stdin);
    freopen("hdoh2795ans.txt","w",stdout);
    while (scanf("%d%d%d",&h,&w,&n)!=EOF)
    {
        BuildTree(1,Min(h,n),1);
        while (n--)
        {
            scanf("%d",&k);
            PointUpdate(k,1);
            printf("%d\n",ans);
        }
    }
    return 0;
}
