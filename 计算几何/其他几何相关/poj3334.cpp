#include<stdio.h>
#include<math.h>

#define eps 1e-8
#define MaxN 1005

//二维点类
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

//二维直线类，一般方程ax+by+c=0
struct Line
{
    double a,b,c,angle;
    Point p1,p2;
    Line(Point s,Point e)
    {
        a=s.y-e.y;
        b=e.x-s.x;
        c=s.x*e.y-e.x*s.y;
        angle=atan2(e.y-s.y,e.x-s.x);
        p1=s;p2=e;
    }
    Line(){}
};

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

//得到sp-op和ep-op的叉积
//>0时ep在opsp的逆时针方向，<0时顺时针，=0时共线
double Cross(Point &sp, Point &ep, Point &op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

//两向量求叉积，求三角形面积需要除以2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//知道直线上两点p1p2，判断直线与线段se是否相交，含顶点
int IsLineIntersectSegment(Line l1,Point s,Point e)
{
    if (Cross(l1.p1,l1.p2,s)*Cross(l1.p1,l1.p2,e)>eps) return 0;
    else return 1;
}

//求两条直线l1和l2的交点
Point GetIntersect(Line l1, Line l2)
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

//求多边形面积，要求点集按逆时针顺序
double ConvexPolygonArea(Point *p,int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

//采用eps的精度判断大/小于零
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//求最大最小值
double max(double a,double b)
{
    if (a<b) return b; else return a;
}

double min(double a,double b)
{
    if (a>b) return b; else return a;
}

Point p[MaxN],q[MaxN];
int pn,qn;
double s;

int Check(double h)
{
    int s1,e1,s2,e2,i;
    double sums;
    Point p1,p2,q1,q2;
    Point tp[MaxN],tq[MaxN];
    Line plane(Point(0,h),Point(1,h));
    
    for (s1=1;p[s1].y<p[s1-1].y;s1++)
        if (IsLineIntersectSegment(plane,p[s1-1],p[s1]))
        {
            p1=GetIntersect(plane,Line(p[s1-1],p[s1]));
            break;
        }
        
    for (e1=pn-2;p[e1].y<p[e1+1].y;e1--)
        if (IsLineIntersectSegment(plane,p[e1+1],p[e1]))
        {
            p2=GetIntersect(plane,Line(p[e1+1],p[e1]));
            break;
        }

    tp[0]=p1;
    for (i=1;i<=e1-s1+1;i++) tp[i]=p[s1+i-1];
    tp[e1-s1+2]=p2;
    sums=ConvexPolygonArea(tp,e1-s1+3);
        
    for (s2=1;q[s2].y<q[s2-1].y;s2++)
        if (IsLineIntersectSegment(plane,q[s2-1],q[s2]))
        {
            q1=GetIntersect(plane,Line(q[s2-1],q[s2]));
            break;
        }

    for (e2=qn-2;q[e2].y<q[e2+1].y;e2--)
        if (IsLineIntersectSegment(plane,q[e2+1],q[e2]))
        {
            q2=GetIntersect(plane,Line(q[e2+1],q[e2]));
            break;
        }
        
    tq[0]=q1;
    for (i=1;i<=e2-s2+1;i++) tq[i]=q[s2+i-1];
    tq[e2-s2+2]=q2;
    sums+=ConvexPolygonArea(tq,e2-s2+3);
    
    return (sums<=s);
}

int main()
{
    int t,i;
    double miny,maxy,mid;
    freopen("poj3334.txt","r",stdin);
    freopen("poj3334ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%lf",&s);
        miny=9999999;
        scanf("%d",&pn);
        for (i=0;i<pn;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            miny=min(miny,p[i].y);
        }
        scanf("%d",&qn);
        for (i=0;i<qn;i++)
        {
            scanf("%lf%lf",&q[i].x,&q[i].y);
            miny=min(miny,q[i].y);
        }
        maxy=min(min(p[0].y,p[pn-1].y),min(q[0].y,q[qn-1].y));
        while (maxy-miny>0.0001) //这里精度不需要eps，因为答案只需要三位
        {
            mid=(maxy+miny)/2;
            if (Check(mid)) miny=mid; else maxy=mid;
        }
        printf("%.3f\n",mid);
    }
    return 0;
}
