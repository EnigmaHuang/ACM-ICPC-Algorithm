#include<cstdio>
#include<cmath>

using namespace std;

#define eps 0.00000001
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

/* 这次不知道为什么下面这种写法失灵了，线段相交判断
用<=的话原题数据过不了，用<的话 
1
1 1 3 3 2 2 2 2
这组数据是错的，所以抄了一种新的写法 

typedef Point Vector;

Vector operator - (Point a,Point b)    
{
    return Vector(a.x-b.x,a.y-b.y);
}

2向量求叉积
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

int IsSegmentIntersect(Point &a1,Point &a2,Point &b1,Point &b2)
{
    double c1=Cross(a2-a1,b1-a1);
    double c2=Cross(a2-a1,b2-a1);
    double c3=Cross(b2-b1,a1-b1);
    double c4=Cross(b2-b1,a2-b1);
    //将下面的<=改为<就可以变成不含端点的情况 
    return (epssgn(c1)*epssgn(c2)<=0 && epssgn(c3)*epssgn(c4)<=0);
}
*/

double Cross(Point sp, Point ep, Point op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}
 
int IsIntersect(Point s1, Point e1, Point s2, Point e2)
{
    if( min(s1.x,e1.x)<= max(s2.x,e2.x) &&
        min(s1.y,e1.y)<= max(s2.y,e2.y) &&
        min(s2.x,e2.x)<= max(s1.x,e1.x) &&
        min(s2.y,e2.y)<= max(s1.y,e1.y) &&
        Cross(s2,e2,s1)*Cross(s2,e2,e1)<=0 &&
        Cross(s1,e1,s2)*Cross(s1,e1,e2)<=0)
    return 1;
    return 0;
}

Point rec[4],seg[2];

int InRect(Point &p)
{
    if (p.x>max(rec[1].x,rec[3].x)) return 0;
    if (p.x<min(rec[1].x,rec[3].x)) return 0;
    if (p.y>max(rec[1].y,rec[3].y)) return 0;
    if (p.y<min(rec[1].y,rec[3].y)) return 0;
    return 1;    
}

int main()
{
    int n,flag;
    freopen("poj1410.txt","r",stdin);
    freopen("poj1410ans.txt","w",stdout);
    scanf("%d",&n);
    while (n--)
    {
        scanf("%lf%lf%lf%lf",&seg[0].x,&seg[0].y,&seg[1].x,&seg[1].y);
        scanf("%lf%lf%lf%lf",&rec[1].x,&rec[1].y,&rec[3].x,&rec[3].y);
        rec[0].x=rec[1].x;
        rec[0].y=rec[3].y;
        rec[2].x=rec[3].x;
        rec[2].y=rec[1].y;
        flag=0;
        if (InRect(seg[0]) || InRect(seg[1])) flag=1;
        else if (IsIntersect(rec[0],rec[1],seg[0],seg[1])) flag=1;
        else if (IsIntersect(rec[1],rec[2],seg[0],seg[1])) flag=1;
        else if (IsIntersect(rec[2],rec[3],seg[0],seg[1])) flag=1;
        else if (IsIntersect(rec[3],rec[0],seg[0],seg[1])) flag=1;
        if (flag) printf("T\n");else printf("F\n");
    }
    return 0; 
}
