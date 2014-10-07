/*
这代码带了输入外挂还是在POJ TLE，但是
在HDOJ 2461上G++ 1531MS，C++ 1718 MS
去掉输入外挂G++ 1968MS，真心坑爹！
*/
#include<stdio.h>
#include<string.h>
#include<algorithm>

#define MaxN 105

using namespace std;

int searchtop,flag;
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
    int l=0,r=searchtop,mid;
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

int allx[MaxN*2];
TScanSegment allseg[MaxN];

inline int ScanInt()
{
    int res=0,ch,flag=0;
    if ((ch=getchar())=='-') flag=1;
    else if (ch>='0' && ch<='9') res=ch-'0';
    while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
    return flag?-res:res;
}

int main()
{
    int n,m,i,j,k,id,cnt;
    int x1,y1,x2,y2,l,r;
    int CaseCnt=0,QueryCnt;
    double ret;
    freopen("poj3695.txt","r",stdin);
    freopen("poj3695ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (n==0 && m==0) break;
        k=0;
            for (i=1;i<=n;i++)
            {
            x1=ScanInt();
            y1=ScanInt();
            x2=ScanInt();
            y2=ScanInt();
            //scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            allx[++k]=x1;
            allseg[k]=TScanSegment(x1,x2,y1,1);
            allx[++k]=x2;
            allseg[k]=TScanSegment(x1,x2,y2,-1);
            }
            printf("Case %d:\n",++CaseCnt);
            QueryCnt=0;
        for (i=1;i<=m;i++)
        {
            k=ScanInt();
            //scanf("%d",&k);
            for (j=0;j<k;j++)
            {
                id=ScanInt();
                //scanf("%d",&id);
                x[2*j]=allx[id*2-1];
                x[2*j+1]=allx[id*2];
                seg[2*j]=allseg[id*2-1];
                seg[2*j+1]=allseg[id*2];
            }
            sort(x,x+2*k);
            sort(seg,seg+2*k);
            cnt=1;
            for (j=1;j<2*k;j++) if (x[j]!=x[j-1]) x[cnt++]=x[j];
            cnt--;
            searchtop=cnt;
            BuildTree(0,cnt,1);
            ret=0;
            for (j=0;j<2*k;j++)
            {
                    l=BinSearch(seg[j].l);
                    r=BinSearch(seg[j].r)-1;
                    if (l<=r)
                    {
                    flag=seg[j].flag;
                    SegmentUpdate(l,r,1);
                    }
                    ret+=node[1].sum*(seg[j+1].h-seg[j].h);
            }
            printf("Query %d: %.0f\n",++QueryCnt,ret);
        }
        printf("\n");
    }
    return 0;
}
