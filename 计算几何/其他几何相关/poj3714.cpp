#include<stdio.h>
#include<math.h>

#define MaxN 100005
#define eps  1e-8
#define INF  99999999.0
#define min(a,b) (a)>(b)?(b):(a)

//二维点类
struct Point
{
    double x,y;
    int id;
    Point(double a=0,double b=0){x=a;y=b;}
};

//求两点之间的直线距离
double dis(Point a,Point b)
{
    if (a.id==b.id) return INF;
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

Point p[2*MaxN],pl[MaxN],pr[MaxN];
int n;

int cmp(const Point &a,const Point &b)
{
    if (a.x==b.x) return (a.y<b.y); else return (a.x<b.x);
}

void QSort(Point p[],int l,int r)
{
    int i=l,j=r;
    Point swap,mid=p[(l+r)/2];
    while (i<=j)
    {
        while (cmp(p[i],mid)) i++;
        while (cmp(mid,p[j])) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

double ShortestDist(int l,int r)
{
    int i,j,mid,cnt1,cnt2;
    double d1,d2,res,tmp;
    if (l==r) return INF;
    if (l-r==1) return dis(p[l],p[r]);
    mid=(l+r)/2;
    d1=ShortestDist(l,mid);
    d2=ShortestDist(mid+1,r);
    res=min(d1,d2);
    cnt1=cnt2=0;
    for (i=mid  ;i>=l;i--) if (p[mid].x-p[i].x<=res) pl[cnt1++]=p[i]; else break;
    for (i=mid+1;i<=r;i++) if (p[i].x-p[mid].x<=res) pr[cnt2++]=p[i]; else break;
    for (i=0;i<cnt1;i++)
        for (j=0;j<cnt2;j++)
        {
            tmp=dis(pl[i],pr[j]);
            res=min(res,tmp);
        }
    return res;
}

int main()
{
    int i,j,t;
    freopen("poj3714.txt","r",stdin);
    freopen("poj3714ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        n*=2;
        for (i=0;i<n;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            if (i<n/2) p[i].id=1; else p[i].id=2;
        }
        QSort(p,0,n-1);
        printf("%.3f\n",ShortestDist(0,n-1));
    }
    return 0;
}
