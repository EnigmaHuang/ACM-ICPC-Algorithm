#include<stdio.h>
#include<string.h>
#include<algorithm>

#define MaxN 205

using namespace std;

int k,flag;
double x[MaxN*2];

struct TScanSegment
{
    double l,r,h;
    int flag;
    TScanSegment() {}
    TScanSegment(double _l,double _r,double _h,int _flag):l(_l),r(_r),h(_h),flag(_flag) {}
    bool operator < (const TScanSegment &cmp) const
    {
        return this->h<cmp.h;
    }
}seg[MaxN];

struct TNode
{
    int l,r;
    int cover;   //区间被多少条线盖住
    double sum;  //被盖住的总长度
}node[3*MaxN];

int BinSearch(double key)
{
    int l=0,r=k,mid;
    while (l<=r)
    {
        mid=(l+r)/2;
        if (key==x[mid]) return mid;
        else if (key<x[mid]) r=mid-1;
        else l=mid+1;
    }
    return -1;
}

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].cover=0;  //一开始的时候没有线段覆盖
    node[u].sum=0;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PushDown(int u)
{
    if (node[u].cover) node[u].sum=x[node[u].r+1]-x[node[u].l];
    else if (node[u].l==node[u].r) node[u].sum=0;
    else node[u].sum=node[u*2].sum+node[u*2+1].sum;
}

void SegmentUpdate(int left,int right,int u)
{
    int mid;
    if (left<=node[u].l && node[u].r<=right)
    {
        node[u].cover+=flag;
        PushDown(u);
        return;
    }
    mid=(node[u].l+node[u].r)/2;
    if (left<=mid) SegmentUpdate(left,right,u*2);
    if (mid<right) SegmentUpdate(left,right,u*2+1);
    PushDown(u);
}

int main()
{
    int n,cas=1,m,i,l,r;
    double x1,y1,x2,y2,ret;
    freopen("poj1151.txt","r",stdin);
    freopen("poj1151ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        m=0;
        for (i=0;i<n;i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            x[m]=x1;
            seg[m++]=TScanSegment(x1,x2,y1,1);
            x[m]=x2;
            seg[m++]=TScanSegment(x1,x2,y2,-1);
        }
        sort(x,x+m);
        sort(seg,seg+m);
        k=1;
        for (i=1;i<m;i++) if (x[i]!=x[i-1]) x[k++]=x[i];
        k--;
        BuildTree(0,k,1);
        ret=0;
        for (i=0;i<m-1;i++)
        {
            l=BinSearch(seg[i].l);
            r=BinSearch(seg[i].r)-1;
            if (l<=r)
            {
                    flag=seg[i].flag;
                    SegmentUpdate(l,r,1);
            }
            ret+=node[1].sum*(seg[i+1].h-seg[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n",cas++,ret);
    }
    return 0;
}
