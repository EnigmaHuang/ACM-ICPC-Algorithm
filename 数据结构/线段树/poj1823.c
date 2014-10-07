#include <stdio.h>
#include <string.h>

#define MaxN 50005
#define Max(a,b) (a)>(b)?(a):(b)
int flag;

struct TNode
{
    int l,r;
    int lma,rma,ma;
    int cover;
}node[MaxN*3];

void BuildTree(int l,int r,int u)
{
    int mid;
    node[u].l=l;
    node[u].r=r;
    node[u].cover=-1;    //初始化为空
    node[u].lma=node[u].rma=node[u].ma=r-l+1;
    if (l==r) return;
    mid=(l+r)/2;
    BuildTree(l,mid,u*2);
    BuildTree(mid+1,r,u*2+1);
}

void PushDown(int u)  //下推状态
{
    node[u*2].cover=node[u*2+1].cover=node[u].cover;
    if (node[u].cover==1)      //全满
    {
        node[u*2].lma=node[u*2].rma=node[u*2].ma=0;
        node[u*2+1].lma=node[u*2+1].rma=node[u*2+1].ma=0;
    }
    else if (node[u].cover==-1) //全空
    {
        node[u*2].lma=node[u*2].rma=node[u*2].ma=node[u*2].r-node[u*2].l+1;
        node[u*2+1].lma=node[u*2+1].rma=node[u*2+1].ma=node[u*2+1].r-node[u*2+1].l+1;
    }
    node[u].cover=0;   //本区间置为不满不空
}

int Query(int num,int u)
{
    if (node[u].lma==num && node[u].r-node[u].l+1==num) return node[u].l;  //区间空数与所需相等，直接返回

    if (node[u].ma>=num)
    {
            //当前区间全满或全空，下推状态
        if (node[u].cover!=0) PushDown(u);
        //左边连续房间数目大于所需，递归左区间
        if (node[u*2].ma >= num) return Query(num,u*2);
        //中间连续房间数目大于所需，返回左子树右边连续的起点
        if (node[u*2].rma+node[u*2+1].lma>=num) return node[u*2].r-node[u*2].rma+1;
        //右边连续空房间数目大于所需，递归右区间
        if (node[u*2+1].ma>=num) return Query(num,u*2+1);
    }
    return 0;
}


void SegmentUpdate(int l, int r,int u)//更新[l,r]区间
{
    int mid,a,b,c;

    if (node[u].l==l && node[u].r==r) //恰好是要更新区间，直接修改该区间状态
    {
        if (flag==-1) node[u].lma=node[u].rma=node[u].ma=r-l+1;
        else node[u].lma=node[u].rma=node[u].ma=0;
        node[u].cover=flag;
        return;
    }

    mid=(node[u].l+node[u].r)/2;

    //当前节点全满或者全空，下推状态
    if (node[u].cover!=0) PushDown(u);

    //向子树更新
    if (r<=mid) SegmentUpdate(l,r,u*2);
    else if (l>mid) SegmentUpdate(l,r,u*2+1);
    else
    {
        SegmentUpdate(l,mid,u*2);
        SegmentUpdate(mid+1,r,u*2+1);
    }

    //左子树全空，则此节点的左连续数等于左子树长度+右子树左连续长度
    //否则节点的左连续数=左子树的左连续数
    if (node[u*2].cover==-1)
         node[u].lma=node[u*2].ma+node[u*2+1].lma;
    else node[u].lma=node[u*2].lma;

    //更新右连续数，原理同左连续数
    if (node[u*2+1].cover==-1)
         node[u].rma=node[u*2+1].ma+node[u*2].rma;
    else node[u].rma=node[u*2+1].rma;

    a=node[u*2].rma+node[u*2+1].lma;    //左右子树相接触的连续数
    b=Max(node[u*2].ma,node[u*2+1].ma); //左右子树各自内部连续数的较大者
    c=Max(node[u].lma,node[u].rma);     //此节点左右连续数的较大者
    node[u].ma=Max(Max(a,b),c);

    //左右子树更新完以后性质一样，需要回溯更新此节点性质
    if (node[u*2].cover==node[u*2+1].cover) node[u].cover=node[u*2].cover;
}

int main()
{
    int n,m,a,b,op;
    freopen("poj1823.txt","r",stdin);
    freopen("poj1823ans.txt","w",stdout);
    scanf("%d%d",&n,&m);
    BuildTree(1,n,1);
    node[1].cover=-1;
    node[1].ma=n;
    while (m--)
    {
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d",&a,&b);
            flag=1;
            SegmentUpdate(a,a+b-1,1);
        }
        else if(op==2)
        {
            scanf("%d%d",&a,&b);
            flag=-1;
            SegmentUpdate(a,a+b-1,1);
        }
        else printf("%d\n",node[1].ma);
    }
    return 0;
}
