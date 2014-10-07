#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps 0.00000001
#define MaxN 101

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

/*
得到sp-op和ep-op的叉积
>0时ep在opsp的逆时针方向，<0时顺时针，=0时共线
*/
inline double Cross(Point sp,Point ep,Point op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

/*知道直线上两点p1p2，判断直线与线段se是否相交，含顶点*/
inline int IsIntersected(Point &p1,Point &p2,Point &s,Point &e)
{
    if (Cross(p1,p2,s)*Cross(p1,p2,e)>eps) return 0;
    else return 1;
}

int n;
Point s[MaxN],e[MaxN];

int Check(Point &p1,Point &p2)
{
    int i;
    if (fabs(p1.x-p2.x)<eps && fabs(p1.y-p2.y)<eps) return 0;
    for (i=0;i<n;i++) if (!IsIntersected(p1,p2,s[i],e[i])) return 0;
    return 1;
}

int main()
{
    int t,i,j,flag;
    freopen("poj3304.txt","r",stdin);
    freopen("poj3304ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++) scanf("%lf%lf%lf%lf",&s[i].x,&s[i].y,&e[i].x,&e[i].y);
        if (n<3) flag=1; else flag=0;
        for (i=0;i<n && !flag;i++)
            for (j=i+1;j<n && !flag;j++)
            {
                if (Check(s[i],s[j])) flag=1;
                else if (Check(s[i],e[j])) flag=1;
                else if (Check(e[i],s[j])) flag=1;
                else if (Check(e[i],e[j])) flag=1;
            }
        if (flag) printf("Yes!\n"); else printf("No!\n");
    }
    return 0;
}
