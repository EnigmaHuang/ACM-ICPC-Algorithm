#include <stdio.h>
#include <algorithm>

using namespace std;

#define MaxN 100005

struct TDivideTree
{
    int n;
    int sorted[MaxN];   //排序后数组
    int sum[20][MaxN];  //sum[i][j]=第i层1~j划分到左子树的元素个数(包括j）
    int data[20][MaxN]; //data[i]=第i层元素序列
    /*-----基本功能-----*/
    void Init(int OriginalData[],int size)
    {
        int i;
        n=size;
        for (i=1;i<=n;i++) sorted[i]=data[0][i]=OriginalData[i];
        sort(sorted+1,sorted+n+1);
        Build(0,1,n);
    }
    void Build(int c,int L,int R)   //建树
    {
        int mid=(L+R)/2;
        int lsame=mid-L+1;    //lsame记录和中间值sorted[mid]相等的，且可分到左孩子的数的个数
        int lp=L,rp=mid+1;    //当前节点的左孩子和右孩子存数的起点
        int i;
        //获得一开始的lsame
        for (i=L;i<mid;i++) if (sorted[i]<sorted[mid]) lsame--;
        for (i=L;i<=R;i++)
        {
            //从前往后遍历一遍确定当前节点区间内的所有元素在哪个孩子中
            if (i==L) sum[c][i]=0;
            else sum[c][i]=sum[c][i-1];
            if (data[c][i]<sorted[mid]) //当前元素比中间值sorted[mid]小，放入左孩子
            {
                data[c+1][lp++]=data[c][i];
                sum[c][i]++;
            }
            //当前元素比中间值sorted[mid]大，放入右孩子
            else if (data[c][i]>sorted[mid]) data[c+1][rp++]=data[c][i];
            else //当前元素值与中间值sorted[mid]相等，根据lsame数判断放入左孩子还是右孩子
            {
                if (lsame)
                {
                    lsame--;
                    sum[c][i]++;
                    data[c+1][lp++]=sorted[mid];
                }
                else data[c+1][rp++]=sorted[mid];
            }
        }
        if (L==R) return;    //到叶子节点，返回
        Build(c+1,L,mid);    //递归进入左孩子区间
        Build(c+1,mid+1,R);  //递归进入右孩子区间
    }
    int Query(int c,int L,int R,int ql,int qr,int k)
    {
        //c为树的层数，L,R为当前节点的区间范围，ql,qr为查询的区间范围，k为查询范围内第k大的数
        int s;  //[L,ql-1]中进入左孩子的元素的个数
        int ss; //[ql,qr]中进入左孩子的元素的个数
        int mid=(L+R)/2;
        if (L==R) return data[c][L]; //到叶子节点直接返回第k大的数
        if (L==ql) //端点重合的情况，单独考虑
        {
            s=0;
            ss=sum[c][qr];
        }
        else
        {
            s=sum[c][ql-1];
            ss=sum[c][qr]-s;
        }
        //左孩子的元素个数大于k个，到左孩子中查询，否则到右孩子中查询
        if (k<=ss) return Query(c+1, L   ,mid,    L+s     ,    L+s+ss-1   ,k);
        else       return Query(c+1,mid+1, R ,mid+1+ql-s-L,mid+1+qr-s-ss-L,k-ss);
    }
    /*-----基本功能结束，下面是应用-----*/
    //[L,R]区间第K大的数
    int KthMaxInRange(int L,int R,int K)
    {
        return Query(0,1,n,L,R,K);
    }
    //求区间[L,R]中第一个比X小的数是第几大的
    int GetXPrecursorRankInRange(int X,int L,int R)
    {
        int mid=(L+R)/2;
        while (L<R)
        {
            if (Query(0,1,n,L,R,mid)<=X) L=mid;
            else R=mid-1;
            mid=(L+R)/2;
        }
        if (Query(0,1,n,L,R,mid)<=X) return mid; else return -1;
    }
    //求区间[L,R]中第一个比X大的数是第几大的
    int GetXSuccessorRankInRange(int X,int L,int R)
    {
        int mid=(L+R)/2;
        while (L<R)
        {
            if (Query(0,1,n,L,R,mid)>=X) R=mid;
            else L=mid+1;
            mid=(L+R)/2;
        }
        if (Query(0,1,n,L,R,mid)>=X) return mid; else return -1;
    }
}DT;

int a[MaxN];

int main()
{
    int i,l,r,n,m,k;
    freopen("poj2104.txt","r",stdin);
    freopen("poj2104ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&a[i]);
        DT.Init(a,n);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",DT.KthMaxInRange(l,r,k));
        }
    }
    return 0;
}
