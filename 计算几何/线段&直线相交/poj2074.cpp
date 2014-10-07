#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define MaxN 105
#define max(a,b) (a)>(b)?(a):(b)

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

struct Line //ax+by+c=0 
{
    double a,b,c;
    Line(Point &p1,Point &p2)
    {
        a=p1.y-p2.y;
        b=p2.x-p1.x;
        c=p1.x*p2.y-p2.x*p1.y;
    }
    Line(){}
};

struct Segment
{
    Point s,e;
    Segment(Point &a,Point &b){s=a;e=b;}
    Segment(double &x1,double &y1,double &x2,double y2)
    {
        s=Point(x1,y1);
        e=Point(x2,y2);
    }
    Segment(){}
};

Point GetIntersect(Line &l1, Line &l2) //取交点 
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

Segment obs[MaxN];      //屏蔽物 
Segment a[MaxN];        //无法看到整间屋子的范围 
double l[MaxN],r[MaxN]; //处理重合的投影 

void QSort(int l,int r)
{
    int i=l,j=r;
    double mid=a[(i+j)/2].s.x;
    Segment swap;
    while (i<=j)
    {
        while (a[i].s.x<mid) i++;
        while (a[j].s.x>mid) j--;
        if (i<=j)
        {
                   swap=a[i];
                   a[i]=a[j];
                   a[j]=swap;
                   i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j); 
}

int main()
{
    int n,i,j;
    double x1,x2,y,ans;
    freopen("poj2074.txt","r",stdin);
    freopen("poj2074ans.txt","w",stdout);
    while (scanf("%lf%lf%lf",&x1,&x2,&y)!=EOF)
    {
        if (fabs(x1)<eps && fabs(x2)<eps && fabs(y)<eps) break;
        Segment house(x1,y,x2,y);
        scanf("%lf%lf%lf",&x1,&x2,&y);
        Segment property(x1,y,x2,y);
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
                   scanf("%lf%lf%lf",&x1,&x2,&y);
                   obs[i]=Segment(x1,y,x2,y);
                   if (y>house.s.y || y<property.s.y)
            {
                n--;
                i--; //不符合要求，过滤掉
            }
        }
        Line prop_line(property.s,property.e);
        for (i=j=0;i<n;i++,j++)  //求出house与每条障碍物在property的投影
        {
                   Line l1(house.s,obs[i].e);
                   Line l2(house.e,obs[i].s);
                   Point p1=GetIntersect(prop_line,l2);
                   Point p2=GetIntersect(prop_line,l1);
                   a[j]=Segment(p1,p2);
                   if (a[j].e.x<property.s.x || a[j].s.x>property.e.x) //投影全在property的外面，排除
                   {
                       j--;
                       continue;
                   }
                   if (a[i].s.x<property.s.x) a[i].s.x=property.s.x;
            if (a[i].e.x>property.e.x) a[i].e.x=property.e.x; 
        }
        n=j;
        if (n==0)  //没有被屏蔽 
        {
                   printf("%.2f\n",property.e.x-property.s.x);
                   continue;
        }
        QSort(0,n-1); //各屏蔽段按起始位置排序 
        l[0]=a[0].s.x;
        r[0]=a[0].e.x;
        for (j=0,i=1;i<n;i++)
        {
            if (r[j]<a[i].s.x)
            {
                       j++;
                       l[j]=a[i].s.x;
                       r[j]=a[i].e.x;
            }
            else r[j]=max(r[j],a[i].e.x);
        }
        ans=max(l[0]-property.s.x,property.e.x-r[j]);
        for (i=0;i<j;i++) ans=max(ans,l[i+1]-r[i]);
        if (ans<eps) printf("No View\n");
        else printf("%.2f\n",ans);
    }
    return 0;
}
