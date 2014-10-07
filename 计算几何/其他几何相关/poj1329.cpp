#include<stdio.h>
#include<math.h>

#define eps 1e-7
#define pi  3.141592653589793

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

double dis(Point &a,Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

Point OutCircleCenter(Point a,Point b,Point c)
{
    Point res;
    double a1=atan2(b.y-a.y,b.x-a.x)+pi/2;
    double a2=atan2(c.y-b.y,c.x-b.x)+pi/2;
    double ax=(a.x+b.x)/2;
    double ay=(a.y+b.y)/2;
    double bx=(c.x+b.x)/2;
    double by=(c.y+b.y)/2;
    double r1=(sin(a2)*(ax-bx)+cos(a2)*(by-ay))/(sin(a1)*cos(a2)-sin(a2)*cos(a1));
    return Point(ax+r1*cos(a1),ay+r1*sin(a1));
}

char fsign(double a)
{
    return a>eps?'-':'+';
}

int main()
{
    Point a,b,c,OCC;  //OCC=Out Circle Center
    double r;
    freopen("poj1329.txt","r",stdin);
    freopen("poj1329ans.txt","w",stdout);
    while (scanf("%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y)!=EOF)
    {
        OCC=OutCircleCenter(a,b,c);
        r=dis(OCC,a);
        printf("(x %c %.3f)^2 + (y %c %.3f)^2 = %.3f^2\n",
               fsign(OCC.x), fabs(OCC.x),
               fsign(OCC.y), fabs(OCC.y), r);
        printf("x^2 + y^2 %c %.3fx %c %.3fy %c %.3f = 0\n",
               fsign(OCC.x), 2*fabs(OCC.x),
               fsign(OCC.y), 2*fabs(OCC.y),
               fsign(-(OCC.x*OCC.x+OCC.y*OCC.y-r*r)),
               fabs(OCC.x*OCC.x+OCC.y*OCC.y-r*r));
        printf("\n");
    }
    return 0;
}
