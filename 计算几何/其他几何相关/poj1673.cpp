#include<stdio.h>
#include<math.h>

#define eps 1e-7

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

struct Line //ax+by+c=0
{
    double a,b,c;
    Point p1,p2;
    Line(Point &s,Point &e)
    {
        a=s.y-e.y;
        b=e.x-s.x;
        c=s.x*e.y-e.x*s.y;
        p1=s;
        p2=e;
    }
    Line(){}
};

Point GetIntersect(Line l1, Line l2) //取交点
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

Point SymPoint(Point p,Line l) //求二维平面上点p关于直线p1p2的对称点
{
    Point result;
    double a=l.p2.x-l.p1.x;
    double b=l.p2.y-l.p1.y;
    double t=((p.x-l.p1.x)*a+(p.y-l.p1.y)*b)/(a*a+b*b);
    result.x=2*l.p1.x+2*a*t-p.x;
    result.y=2*l.p1.y+2*b*t-p.y;
    return result;
}

int main()
{
    int n;
    Point a,b,c,asym,bsym,its;
    freopen("poj1673.txt","r",stdin);
    freopen("poj1673ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        while (n--)
        {
            scanf("%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y);
            asym=SymPoint(a,Line(b,c));
            bsym=SymPoint(b,Line(a,c));
            its=GetIntersect(Line(a,asym),Line(b,bsym));
            printf("%.4f %.4f\n",its.x+eps,its.y+eps);
        }
    }
    return 0;
}
