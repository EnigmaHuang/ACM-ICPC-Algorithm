#include<stdio.h>
#include<string.h>

#define MaxN 100005

struct TNode
{
    int l,r,kind,sum;
}node[MaxN*3];

int newkind;

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].sum=right-left+1;  //一开始都是种类1，可以直接算价值和
    node[u].kind=1;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PushDown(int u)
{
    node[u*2].kind=node[u].kind;
    node[u*2].sum=(node[u*2].r-node[u*2].l+1)*node[u*2].kind;
    node[u*2+1].kind=node[u].kind;
    node[u*2+1].sum=(node[u*2+1].r-node[u*2+1].l+1)*node[u*2+1].kind;
    node[u].kind=0;
}

void SegmentUpdate(int left,int right,int u)
{
    int mid;
    if (node[u].kind==newkind) return; //剪枝，种类相同不更新
    if (left<=node[u].l && node[u].r<=right)
    {
        node[u].kind=newkind;
        node[u].sum=newkind*(node[u].r-node[u].l+1);
        return;
    }
    
    if (node[u].kind!=0) PushDown(u);
    
    mid=(node[u].l+node[u].r)/2;
    if (right<=mid) SegmentUpdate(left,right,u*2);
    else if (left>mid) SegmentUpdate(left,right,u*2+1);
    else
    {
        SegmentUpdate(left,mid,u*2);
        SegmentUpdate(mid+1,right,u*2+1);
    }
    node[u].sum=node[u*2].sum+node[u*2+1].sum;
}

int main()
{
    int t,q,n,l,r,i;
    freopen("hdoj1698.txt","r",stdin);
    freopen("hdoj1698ans.txt","w",stdout);
    scanf("%d",&t);
    for (i=1;i<=t;i++)
    {
        scanf("%d",&n);
        BuildTree(1,n,1);
        scanf("%d",&q);
        while (q--)
        {
            scanf("%d%d%d",&l,&r,&newkind);
            SegmentUpdate(l,r,1);
        }
        printf("Case %d: The total value of the hook is %d.\n",i,node[1].sum);
    }
    return 0;
}
