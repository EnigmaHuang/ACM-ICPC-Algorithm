#include<stdio.h>
#include<math.h>

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

Vector operator - (Point &a,Point &b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2向量求叉积，同时也可以求面积 */
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

Point BaryCenter(int n,Point *p)
{
    Point res(0,0);
    double s=0.0,t;
    int i;
    for (i=1;i<n-1;i++)
    {
        t=Cross(p[i]-p[0],p[i+1]-p[0])/2;   //分割成三角形，算面积
        s+=t;
        res.x+=(p[0].x+p[i].x+p[i+1].x)*t;  //将面积作为重量放在三角形的重心上
        res.y+=(p[0].y+p[i].y+p[i+1].y)*t;  //质量*坐标，三角形重心所需的除以3放在后面
    }
    res.x/=(3*s);
    res.y/=(3*s);
    return res;
}

int main()
{
    int t,n,i;
    Point ans,*p;
    freopen("poj1385.txt","r",stdin);
    freopen("poj1385ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        p=new Point[n];
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        ans=BaryCenter(n,p);
        printf("%.2f %.2f\n",ans.x,ans.y);
        delete []p;
    }
    return 0;
}
