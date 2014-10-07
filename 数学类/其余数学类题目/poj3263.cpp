#include<stdio.h>
#include<string.h>

#define MaxN 10005

struct TSegment
{
    int l,r;
}seg[MaxN];

int offset[MaxN];

inline int cmp(TSegment s1,TSegment s2)
{
    if (s1.l==s2.l) return (s1.r<s2.r);
    else return (s1.l<s2.l);
}

void QSort(int l,int r)
{
    int i=l,j=r;
    TSegment swap,mid;
    mid=seg[(l+r)/2];
    while (i<=j)
    {
        while (cmp(seg[i],mid)) i++;
        while (cmp(mid,seg[j])) j--;
        if (i<=j)
        {
            swap=seg[i];
            seg[i]=seg[j];
            seg[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int main()
{
    int n,m,h,r,i,t,ans;
    freopen("poj3263.txt","r",stdin);
    freopen("poj3263ans.txt","w",stdout);
    while (scanf("%d%d%d%d",&n,&m,&h,&r)!=EOF)
    {
        for (i=1;i<=r;i++)
        {
            scanf("%d%d",&seg[i].l,&seg[i].r);
            if (seg[i].l>seg[i].r)
            {
                t=seg[i].l;
                seg[i].l=seg[i].r;
                seg[i].r=t;
            }
        }
        QSort(1,r);
        memset(offset,0,sizeof(offset));
        seg[0].l=seg[0].r=0;
        for (i=1;i<=r;i++)
        {
            if (seg[i].l==seg[i-1].l && seg[i].r==seg[i-1].r) continue;
            //进入了[seg[i].l+1,seg[i].r-1]区间后比seg[i].l最少矮1
            //所以加上一个偏移标记
            offset[seg[i].l+1]--;
            offset[seg[i].r]++;
        }
        ans=h;
        for (i=1;i<=n;i++)
        {
            ans+=offset[i];
            printf("%d\n",ans);
        }
    }
    return 0;
}
