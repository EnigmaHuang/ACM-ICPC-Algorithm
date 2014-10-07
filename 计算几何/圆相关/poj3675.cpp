#include<stdio.h>
#include<math.h>

#define eps  1e-8
#define pi   3.141592653589793
#define MaxN 100001

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

Vector operator + (Point &a,Point &b)
{
    return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (Point &a,Point &b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

//2向量求叉积
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

double Dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
}

//采用eps的精度判断大/小于零
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

double len(Point a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}

Point res[MaxN];
double r;

double min(double a,double b)
{
    return a<b?a:b;
}

//红书《算法与实现》的模板，求扇形面积
double SectorArea(Point &a,Point &b)
{
    double theta=atan2(a.y,a.x)-atan2(b.y,b.x);
    while (theta<=0) theta+=2*pi;
    while (theta>=2*pi) theta-=2*pi;
    theta=min(theta,2*pi-theta);
    return r*r*theta/2;
}

//红书《算法与实现》的模板，求园与线段（直线）的交点
void CircleCrossLine(Point a,Point b,Point o,double r,Point ret[],int &num)
{
    double x0=o.x,y0=o.y;
    double x1=a.x,y1=a.y;
    double x2=b.x,y2=b.y;
    double dx=x2-x1,dy=y2-y1;
    double A=dx*dx+dy*dy;
    double B=2*dx*(x1-x0)+2*dy*(y1-y0);
    double C=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
    double delta=B*B-4*A*C;
    num=0;
    if (epssgn(delta)>=0)
    {
        double t1=(-B-sqrt(fabs(delta)))/(2*A);
        double t2=(-B+sqrt(fabs(delta)))/(2*A);
        if (epssgn(t1-1.0)<=0 && epssgn(t1)>=0)
            ret[num++]=Point(x1+t1*dx,y1+t1*dy);
        if (epssgn(t2-1.0)<=0 && epssgn(t2)>=0)
            ret[num++]=Point(x1+t2*dx,y1+t2*dy);
    }
}

double Calc(Point &a,Point &b)  //红书模板
{
    Point p[2];
    int num=0;
    int ina=(epssgn(len(a)-r)<0);
    int inb=(epssgn(len(b)-r)<0);
    if (ina)
    {
        if (inb) return fabs(Cross(a,b))/2.0; //情形1
        else  //情形2
        {
            CircleCrossLine(a,b,Point(0,0),r,p,num);
            return SectorArea(b,p[0])+fabs(Cross(a,p[0]))/2.0;
        }
    }
    else
    {
       CircleCrossLine(a,b,Point(0,0),r,p,num);
        if (inb) return SectorArea(p[0],a)+fabs(Cross(p[0],b))/2.0; //情形2
        else
        {
            if (num==2) return SectorArea(a,p[0])+SectorArea(p[1],b)+fabs(Cross(p[0],p[1]))/2.0; //情形4
            else return SectorArea(a,b); //情形3
        }
    }
}

int main()
{
    int i,n,sgn;
    double ans;
    freopen("poj3675.txt","r",stdin);
    freopen("poj3675ans.txt","w",stdout);
    while (scanf("%lf%d",&r,&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&res[i].x,&res[i].y);
        res[n]=res[0];
        ans=0;
        for (i=0;i<n;i++)
        {
            sgn=epssgn(Cross(res[i],res[i+1]));
            if (sgn!=0) ans+=sgn*Calc(res[i],res[i+1]);
        }
        printf("%.2f\n",fabs(ans));
    }
    return 0;
}
