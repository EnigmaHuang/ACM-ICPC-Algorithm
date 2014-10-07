#include<stdio.h>
#include<math.h>

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2向量求叉积，同时也可以求面积 */
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

int gcd(int a,int b)
{
    return b>0?gcd(b,a%b):a;
}

int iabs(int x)
{
    if (x>0) return x; else return -x;
}

int main()
{
    int i,onedge,intriangle,flag;
    double s;
    Point p[3];
    freopen("poj2954.txt","r",stdin);
    freopen("poj2954ans.txt","w",stdout);
    while (1)
    {
        flag=1;
        for (i=0;i<3;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            if (p[i].x || p[i].y) flag=0;
        }
        if (flag) break;
        onedge=0;
        for (i=0;i<3;i++) onedge+=gcd(iabs(p[i].x-p[(i+1)%3].x),iabs(p[i].y-p[(i+1)%3].y));
        s=fabs(Cross(p[1]-p[0],p[2]-p[0]))/2;
        intriangle=(int)s-onedge/2+1;
        printf("%d\n",intriangle);
    }
    return 0;
}
