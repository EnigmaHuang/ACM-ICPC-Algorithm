#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define INF 1e20
#define MaxN 35
#define max(a,b) (a)>(b)?(a):(b)

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

typedef Point Vector;

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

Point GetIntersect(Line &l1, Line &l2) //取交点 
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

Vector operator - (Point a,Point b)    
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2向量求叉积*/
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

/*求多边形面积，要求点集按逆时针顺序*/
double ConvexPolygonArea(Point * p,int n)
{
    double area=0;
    int i;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

int n;
Point map[MaxN][MaxN];
double p[4][MaxN];

void BuildMap()
{
    int i,j;
    for (i=0;i<=n+1;i++)
    {
        Point p1(0,p[2][i]),p2(1,p[3][i]);
        Line l1(p1,p2); //横边
        for (j=0;j<=n+1;j++)
        {
            p1=Point(p[0][j],0);
            p2=Point(p[1][j],1);
            Line l2(p1,p2);  //纵边
            map[i][j]=GetIntersect(l1,l2);
        }
    }
}

int main()
{
    int i,j;
    double area,ans;
    Point rect[4];
    freopen("poj1408.txt","r",stdin);
    freopen("poj1408ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<4;i++)
        {
                   p[i][0]=0;  //把正方形四条边加进去
            p[i][n+1]=1;
                   for (j=1;j<=n;j++) scanf("%lf",&p[i][j]);
        }
        BuildMap();
        ans=0;
        for (i=0;i<=n;i++)
            for (j=0;j<=n;j++)
            {
                       rect[0]=map[i][j];
                       rect[1]=map[i][j+1];
                       rect[2]=map[i+1][j+1];
                       rect[3]=map[i+1][j];
                       area=ConvexPolygonArea(rect,4);
                       ans=max(area,ans);
            }
        printf("%.6f\n",ans);
    }
    return 0;
} 
