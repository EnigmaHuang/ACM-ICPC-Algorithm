#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define MaxN 10005
#define Max(a,b) (a)>(b)?(a):(b)

struct TNode
{
    int l,r;
    long long summax,addpush;
}node[MaxN*8];

struct TLine
{
    long long x,y1,y2,val;
    bool operator < (TLine l2) const
    {
        if (this->x==l2.x) return (this->val>l2.val);
        else return (this->x<l2.x);
    }
}seg[MaxN*2];

long long y[MaxN*2];
long long val;

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].summax=node[u].addpush=0;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PushDown(int u)
{
    node[u*2  ].summax  += node[u].addpush;
    node[u*2  ].addpush += node[u].addpush;
    node[u*2+1].summax  += node[u].addpush;
    node[u*2+1].addpush += node[u].addpush;
    node[u].addpush=0;
}

void SegmentUpdate(long long left,long long right,int u)
{
    int mid;
    if (left==y[node[u].l] && right==y[node[u].r])
    {
        node[u].summax+=val;
        node[u].addpush+=val;
        return;
    }
    if (node[u].l==node[u].r) return;

    if (node[u].addpush) PushDown(u);

    mid=(node[u].l+node[u].r)/2;
    if (right<=y[mid]) SegmentUpdate(left,right,u*2);
    else if (left>=y[mid+1]) SegmentUpdate(left,right,u*2+1);
    else
    {
        SegmentUpdate(left,y[mid],u*2);
        SegmentUpdate(y[mid+1],right,u*2+1);
    }
    
    node[u].summax=Max(node[u*2].summax,node[u*2+1].summax);
}

int main()
{
    int n,w,h,i,k;
    long long ans;
    freopen("poj2482.txt","r",stdin);
    freopen("poj2482ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&w,&h)!=EOF)
    {
        for (i=0;i<n;i++)
        {
            scanf("%lld%lld%lld",&seg[i].x,&seg[i].y1,&seg[i].val);
            y[i*2+1]=seg[i].y1;
            y[i*2+2]=seg[i].y1+h-1;
            seg[i].y2=seg[i].y1+h-1;
            seg[n+i]=seg[i];
            seg[n+i].x=seg[i].x+w-1;
            seg[n+i].val=-seg[i].val;
        }
        sort(y+1,y+2*n+1);
        sort(seg,seg+2*n);

        k=1;
        for (i=2;i<=2*n;i++) if (y[i]!=y[i-1]) y[++k]=y[i];

        BuildTree(1,k,1);
        ans=0;
        for (i=0;i<2*n;i++)
        {
            val=seg[i].val;
            SegmentUpdate(seg[i].y1,seg[i].y2,1);
            ans=Max(ans,node[1].summax);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
