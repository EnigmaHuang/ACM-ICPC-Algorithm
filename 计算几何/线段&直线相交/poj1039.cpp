#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define INF 1e20
#define MaxN 25
#define max(a,b) (a)>(b)?(a):(b)

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

Point a[MaxN],b[MaxN];
double ans;
int n;

int Check(Point &p1,Point &p2,int x)
{
    int i,flag;
    for (i=1;i<n;i++)
    {
            //如果光线穿过光缆，则所有上侧的点与p1组成的向量都应该在光线的逆时针方向
        if (Cross(p2,a[i],p1)<-eps || Cross(p2,a[i+1],p1)<-eps)
        {
                   flag=1;
                   break;
        }
        //如果光线穿过光缆，则所有下侧的点与p1组成的向量都应该在光线的顺时针方向 
        if (Cross(p2,b[i],p1)>eps  || Cross(p2,b[i+1],p1)>eps)
        {
                   flag=2;
                   break;
        }
    }
    if (i==n) return 1;  //没有和任何管道相交
    if (i<x) return 0;   //光线不合法
    Line l1(p1,p2),l2;
    if (flag==1) l2=Line(a[i],a[i+1]);
    else l2=Line(b[i],b[i+1]);
    ans=max(ans,((l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b)));
    return 0;
} 

int main()
{
    int i,j,flag;
    freopen("poj1039.txt","r",stdin);
    freopen("poj1039ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=1;i<=n;i++)
        {
                   scanf("%lf%lf",&a[i].x,&a[i].y);
                   b[i].x=a[i].x;
                   b[i].y=a[i].y-1;
        }
        ans=-INF;
        if (n<3) flag=1;
        for (i=1;i<=n;i++)
        {
            for (j=i+1;j<=n;j++)
            {
                       flag=Check(a[i],b[j],j);
                       if (flag) break;
                       flag=Check(b[i],a[j],j);
                       if (flag) break;
            }
            if (flag) break;
        }
        if (flag) printf("Through all the pipe.\n");
        else printf("%.2f\n",ans);
    }
    return 0;
} 
