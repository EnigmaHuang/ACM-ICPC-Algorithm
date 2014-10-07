#include<stdio.h>
#include<string.h>

#define MaxN 50005

struct TNode
{
    int l,r,sum;
}node[MaxN*3];

int num[MaxN],add,ans;

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    if (left==right)
    {
        node[u].sum=num[left];
        return;
    }
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
    node[u].sum=node[u*2].sum+node[u*2+1].sum;
}

void PointUpdate(int left,int right,int k,int u)
{
    int mid;
    if (left==right)
    {
        node[u].sum+=add;
        return;
    }
    mid=(node[u].l+node[u].r)/2;
    if (k<=mid) PointUpdate(left,mid,k,u*2);
    else PointUpdate(mid+1,right,k,u*2+1);
    node[u].sum=node[u*2].sum+node[u*2+1].sum;
}

void SegmentQuery(int left,int right,int u,int ql,int qr)
{
    int mid;
    if (ql<=left && right<=qr)
    {
        ans+=node[u].sum;
        return;
    }
    mid=(node[u].l+node[u].r)/2;
    if (qr<=mid) SegmentQuery(left,mid,u*2,ql,qr);
    else if (ql>mid) SegmentQuery(mid+1,right,u*2+1,ql,qr);
    else
    {
        SegmentQuery(left,mid,u*2,ql,qr);
        SegmentQuery(mid+1,right,u*2+1,ql,qr);
    }
}

int main()
{
    int n,t,i,k;
    int l,r,x;
    char cmd[10];
    freopen("hdoj1166.txt","r",stdin);
    freopen("hdoj1166ans.txt","w",stdout);
    scanf("%d",&t);
    for (k=1;k<=t;k++)
    {
        scanf("%d",&n);
        for (i=1;i<=n;i++) scanf("%d",&num[i]);
        BuildTree(1,n,1);
        scanf("%s",cmd);
        printf("Case %d:\n",k);
        while (strcmp(cmd,"End")!=0)
        {
            if (cmd[0]=='Q')
            {
                scanf("%d%d",&l,&r);
                ans=0;
                SegmentQuery(1,n,1,l,r);
                printf("%d\n",ans);
            }
            else if (cmd[0]=='A')
            {
                scanf("%d%d",&x,&add);
                PointUpdate(1,n,x,1);
            }
            else
            {
                scanf("%d%d",&x,&add);
                add=0-add;
                PointUpdate(1,n,x,1);
            }
            scanf("%s",cmd);
        }
    }
    return 0;
}
