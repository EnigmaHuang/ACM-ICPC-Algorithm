#include<stdio.h>
#define MaxN 1005

struct TPoint
{
    int x,y;
}point[MaxN];

int n;

inline int cmp(const TPoint &tp1,const TPoint &tp2)
{
    if (tp1.x==tp2.x) return (tp1.y<tp2.y);
    else return (tp1.x<tp2.x);
}

void QSort(int l,int r)
{
    int i=l,j=r;
    TPoint mid,swap;
    mid=point[(l+r)/2];
    while (i<=j)
    {
        while (cmp(point[i],mid)) i++;
        while (cmp(mid,point[j])) j--;
        if (i<=j)
        {
            swap=point[i];
            point[i]=point[j];
            point[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

inline int BinSearch(int x,int y)
{
    int l=1,r=n,mid;
    TPoint target;
    target.x=x;
    target.y=y;
    while (r>=l)
    {
        mid=(l+r)/2;
        if (point[mid].x==x && point[mid].y==y) return 1;
        if (cmp(point[mid],target)) l=mid+1; else r=mid-1;
    }
    return 0;
}

int main()
{
    int x,y,i,j,cnt,x2,y2;
    freopen("poj2002.txt","r",stdin);
    freopen("poj2002ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=1;i<=n;i++) scanf("%d%d",&point[i].x,&point[i].y);
        QSort(1,n);
        cnt=0;
        for (i=1;i<=n;i++)
            for (j=i+1;j<=n;j++)
            {
       	        x=point[i].y-point[j].y+point[i].x;
       	        y=point[j].x-point[i].x+point[i].y;
       	        if (!BinSearch(x,y)) continue;
       	        x2=point[i].y-point[j].y+point[j].x;
       	        y2=point[j].x-point[i].x+point[j].y;
       	        if (BinSearch(x2,y2)) cnt++;
            }
        printf("%d\n",cnt/2);
    }
    return 0;
}
