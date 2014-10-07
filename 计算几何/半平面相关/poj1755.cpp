#include <cstdio>
#include <cmath>

using namespace std;

#define eps  1e-16
#define MaxN 101
#define INF  99999999

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
    Line(double _a,double _b,double _c):a(_a),b(_b),c(_c)
    {
        p1.x=0;
        p1.y=(-c-a*p1.x)/b;
        p2.x=1;
        p1.y=(-c-a*p2.x)/b;
    }
    Line(){}
};

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

//两向量求叉积，求三角形面积需要除以2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//采用eps的精度判断大/小于零
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//求两条直线l1和l2的交点
Point GetIntersect(Line l1, Line l2)
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

/*-----半平面交模板-----*/
//p是现在切出来的半平面的点，pn是点的数量，需要按顺时针或者逆时针排序
//新的半平面直线为ax+by+c=0
void HalfPlaneCut(Point p[],int &pn,double a,double b,double c)
{
    int cnt=0,i;
    Point tp[MaxN];  //temp_p
    //现在交出来的点在新的半平面内，保留
    for (i=1;i<=pn;i++) if (epssgn(a*p[i].x+b*p[i].y+c)>=0) tp[++cnt]=p[i];
    else //否则如果其前后的点在半平面内，重新切割
    {
        if (epssgn(a*p[i-1].x+b*p[i-1].y+c)>0)
            tp[++cnt]=GetIntersect(Line(p[i-1],p[i]),Line(a,b,c));
        if (epssgn(a*p[i+1].x+b*p[i+1].y+c)>0)
            tp[++cnt]=GetIntersect(Line(p[i],p[i+1]),Line(a,b,c));
    }
    pn=cnt;
    for (i=1;i<=cnt;i++) p[i]=tp[i];
    p[0]=p[cnt];
    p[cnt+1]=p[1];
}
/*-----半平面交模板-----*/

Point p[MaxN];
int n,pn;
double u[MaxN],v[MaxN],w[MaxN];

//求多边形面积，要求点集按逆时针顺序
double ConvexPolygonArea(Point *p,int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

int Check(int idx)
{
    int i;
    Point p1,p2;
    double a,b,c,s;
    //给定外围空间
    p[1]=Point(0,0);
    p[2]=Point(0,INF);
    p[3]=Point(INF,INF);
    p[4]=Point(INF,0);
    p[5]=p[1];
    p[0]=p[4];
    pn=4;
    for (i=0;i<n;i++) if (i!=idx)
    {
        a=(u[idx]-u[i])/(u[idx]*u[i]);
        b=(v[idx]-v[i])/(v[idx]*v[i]);
        c=(w[idx]-w[i])/(w[idx]*w[i]);
        if (a==0 && b==0 && c<eps) return 0;
        HalfPlaneCut(p,pn,a,b,c);
    }
    s=fabs(ConvexPolygonArea(p,pn));  //这题eps精度卡到1e-16
    if (epssgn(s)==0) return 0; else return 1;
}

int main()
{
    int i;
    freopen("poj1755.txt","r",stdin);
    freopen("poj1755ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        for (i=0;i<n;i++) scanf("%lf%lf%lf",&u[i],&v[i],&w[i]);
        for (i=0;i<n;i++) if (Check(i)) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}
