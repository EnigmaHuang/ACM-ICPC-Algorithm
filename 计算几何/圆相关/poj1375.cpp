#include<stdio.h>
#include<math.h>

#define MaxN 501
#define max(a,b) (a)>(b)?(a):(b)

//二维点类
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

struct XAxisLine
{
    double l,r;
}line[MaxN];

//求两点之间的直线距离
double dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void QSort(XAxisLine line[],int l,int r)
{
    int i=l,j=r;
    XAxisLine mid=line[(l+r)/2],swap;
    while (i<=j)
    {
        while (line[i].l<mid.l) i++;
        while (line[j].l>mid.l) j--;
        if (i<=j)
        {
            swap=line[i];
            line[i]=line[j];
            line[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(line,i,r);
    if (l<j) QSort(line,l,j);
}

int main()
{
    int n,i;
    double r,a,b,d,angle1,angle2,left,right;
    Point p,q;
    freopen("poj1375.txt","r",stdin);
    freopen("poj1375ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        scanf("%lf%lf",&p.x,&p.y);
        for (i=0;i<n;i++)
        {
            scanf("%lf%lf%lf",&q.x,&q.y,&r);
            d=dis(p,q);
            a=asin(r/d);
            b=asin((p.x-q.x)/d);
            angle1=b+a;
            angle2=b-a;
            line[i].l=p.x-p.y*tan(angle1);
            line[i].r=p.x-p.y*tan(angle2);
        }
        QSort(line,0,n-1);
        left=line[0].l;
        right=line[0].r;
        for (i=1;i<n;i++)
        {
            if (line[i].l>right)
            {
                printf("%.2f %.2f\n",left,right);
                left=line[i].l;
                right=line[i].r;
            }
            else right=max(line[i].r,right);
        }
        printf("%.2f %.2f\n\n",left,right);
    }
    return 0;
}

