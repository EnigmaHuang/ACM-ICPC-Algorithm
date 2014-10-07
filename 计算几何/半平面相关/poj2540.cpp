#include <cstdio>
#include <cmath>

using namespace std;

#define eps  1e-16
#define MaxN 101

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

//求多边形面积，要求点集按逆时针顺序
double ConvexPolygonArea(Point *p,int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

Line GetMidVertical(Point p1,Point p2)
{
    Point p3((p1.x+p2.x)/2,(p1.y+p2.y)/2);
    double a=p1.x-p2.x;
    double b=p1.y-p2.y;
    double c=-a*p3.x-b*p3.y;
    return Line(a,b,c);
}

int main()
{
    int i,flag=0;
    Point pre(0,0),now;
    char str[255];
    freopen("poj2540.txt","r",stdin);
    freopen("poj2540ans.txt","w",stdout);
    //给定外围空间
    p[1]=Point(0,0);
    p[2]=Point(0,10);
    p[3]=Point(10,10);
    p[4]=Point(10,0);
    p[5]=p[1];
    p[0]=p[4];
    pn=4;
    while (scanf("%lf%lf%s",&now.x,&now.y,str)!=EOF)
    {
        Line l=GetMidVertical(pre,now);
        if (str[0]=='C')
        {
            //调整一下方向，确保距离目标点更近的一点在直线左侧
            if (epssgn(l.a*pre.x+l.b*pre.y+l.c)<0)
            {
                l.a=-l.a;
                l.b=-l.b;
                l.c=-l.c;
            }
        }
        else if (str[0]=='H')
        {
            //调整一下方向，确保距离目标点更近的一点在直线左侧
            if (epssgn(l.a*now.x+l.b*now.y+l.c)<0)
            {
                l.a=-l.a;
                l.b=-l.b;
                l.c=-l.c;
            }
        }
        else flag=1;
        if (flag)
        {
            printf("0.00\n");
            continue;
        }
        HalfPlaneCut(p,pn,l.a,l.b,l.c);
        printf("%.2f\n",fabs(ConvexPolygonArea(p,pn)));
        pre=now;
    }
    return 0;
}
