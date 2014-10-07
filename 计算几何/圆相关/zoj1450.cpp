#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define eps 1e-8
#define MaxN 101

//二维点类
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

//求两点之间的直线距离
double dis(Point &a,Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

//采用eps的精度判断大/小于零
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//三点确定圆心
Point GetCircleCenter(Point &a,Point &b,Point &c)
{
    double a1=b.x-a.x, b1=b.y-a.y, c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x, b2=c.y-a.y, c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    return Point(a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d);
}

//两点求圆心
Point GetCircleCenter(Point &p1,Point &p2)
{
    return Point((p1.x+p2.x)/2,(p1.y+p2.y)/2);
}

//求有p[]中n个点的最小圆覆盖，返回圆心center和半径r
void MinCircleCover(Point p[],int n,Point &center,double &r)
{
    int i,j,k;
    random_shuffle(p,p+n); //先随机化打乱点的顺序
    r=0;
    center=p[0];
    for (i=1;i<n;i++) if (dis(p[i],center)+eps>r)
    {
        center=p[i];
        r=0;
        for (j=0;j<i;j++) if (dis(p[j],center)+eps>r)
        {
            center.x=(p[i].x+p[j].x)/2;
            center.y=(p[i].y+p[j].y)/2;
            r=dis(center,p[j]);
            fprintf(stderr,"center=(%.1f,%.1f) p[j]=(%.1f,%.1f) r=%.1f\n",center.x,center.y,p[j].x,p[j].y,r);
            for (k=0;k<j;k++) if (dis(p[k],center)+eps>r)
            {
                center=GetCircleCenter(p[i],p[j],p[k]);
                r=dis(center,p[k]);
                fprintf(stderr,"center=(%.1f,%.1f) p[k]=(%.1f,%.1f) r=%.1f\n",center.x,center.y,p[k].x,p[k].y,r);
            }
        }
    }
}

Point center,p[MaxN];
double r;
int n;

int main()
{
    int i;
    freopen("zoj1450.txt","r",stdin);
    freopen("zoj1450ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        MinCircleCover(p,n,center,r);
        printf("%.2f %.2f %.2f\n",center.x,center.y,r);
        fprintf(stderr,"\n");
    }
    return 0;
}
