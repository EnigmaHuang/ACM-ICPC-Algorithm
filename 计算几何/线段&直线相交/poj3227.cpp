#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define MaxN 1005 

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

/*
得到sp-op和ep-op的叉积
>0时ep在opsp的逆时针方向，<0时顺时针，=0时共线 
*/ 
double Cross(Point sp,Point ep,Point op) 
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

/*知道直线上两点p1p2，判断直线se与线段是否相交，含顶点*/
int IsIntersected(Point &p1,Point &p2,Point &s,Point &e)
{
    if (Cross(p1,p2,s)*Cross(p1,p2,e)>eps) return 0;
    else return 1;    
}

Point GetIntersect(Line l1, Line l2) //取交点 
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

double dist(Point &p1,Point &p2)
{
    double a=p1.x-p2.x;
    double b=p1.y-p2.y;
    return sqrt(a*a+b*b);
}

Point p[MaxN];

int main()
{
    int n,h,i;
    double nowk,newk,ans;
    Point nowp,its;
    freopen("poj3227.txt","r",stdin);
    freopen("poj3227ans.txt","w",stdout);
    while (scanf("%d%d",&n,&h))
    {
        if (n==0 && h==0) break;
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        Point start(0,h);
        nowk=(p[1].y-1.0*h)/p[1].x;
        nowp=p[1];
        ans=dist(p[0],p[1]);
        for (i=2;i<n;i++)
        {
            newk=(p[i].y-1.0*h)/p[i].x;
            if (newk-nowk>eps) //新的山顶比现在的角度更大
            {
                //if (IsIntersected(start,nowp,p[i],p[i-1]))  这句多余 
                its=GetIntersect(Line(start,nowp),Line(p[i],p[i-1]));
                ans+=dist(its,p[i]);
                nowk=newk;
                nowp=p[i];
            }
        }
        printf("%.2f\n",ans);
    }
    return 0;
} 
