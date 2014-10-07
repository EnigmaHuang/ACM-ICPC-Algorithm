#include<cstdio>
#include<cmath>

using namespace std;

#define eps 0.00000001

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
};

inline bool Parallel(Line &l1,Line &l2)
{
    return (abs(l1.a*l2.b-l2.a*l1.b)<eps);
}

inline bool LineEqual(Line &l1,Line &l2)
{
    if (!Parallel(l1,l2)) return 0;
    else return (abs(l1.a*l2.c-l2.a*l1.c)<eps && abs(l1.b*l2.c-l2.b*l1.c)<eps);
}

Point GetIntersect(Line &l1, Line &l2) //È¡½»µã 
{
    Point res;
    if (Parallel(l1,l2)) return res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

int main()
{
    int t,i;
    Point p[4],ans;
    freopen("poj1269.txt","r",stdin);
    freopen("poj1269ans.txt","w",stdout);
    scanf("%d",&t);
    printf("INTERSECTING LINES OUTPUT\n");
    while (t--)
    {
        for (i=0;i<4;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        Line l1(p[0],p[1]),l2(p[2],p[3]);
        if (LineEqual(l1,l2)) printf("LINE\n");
        else if (Parallel(l1,l2)) printf("NONE\n");
        else 
        {
                   ans=GetIntersect(l1,l2);
                   printf("POINT %.2f %.2f\n",ans.x,ans.y);
        }
    }
    printf("END OF OUTPUT\n");
    return 0;
}


