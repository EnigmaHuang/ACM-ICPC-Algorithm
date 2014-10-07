#include <cstdio>
#include <cmath>

using namespace std;

#define eps  1e-8
#define MaxN 101

//二维点类
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

//二维直线类，一般方程ax+by+c=0
struct Line
{
    double a,b,c,angle;
    Point p1,p2;
    Line(Point s,Point e)
    {
        a=s.y-e.y;
        b=e.x-s.x;
        c=s.x*e.y-e.x*s.y;
        angle=atan2(e.y-s.y,e.x-s.x);
        p1=s;p2=e;
    }
    Line(){}
};

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

//两向量求叉积，求三角形面积需要除以2
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

//求两条直线l1和l2的交点
Point GetIntersect(Line l1, Line l2)
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

/*-----半平面交模板-----*/
int cmp(const Line & l1,const Line & l2)
{
    int d=epssgn(l1.angle-l2.angle);
    if (!d) return (epssgn(Cross(l2.p1-l1.p1,l2.p2-l1.p1))>0); //极角相同时，将更靠半平面里面的放在前面
    return d<0;
}

void QSort(Line L[],int l,int r)
{
    int i=l,j=r;
    Line swap,mid=L[(l+r)/2];
    while (i<=j)
    {
        while (cmp(L[i],mid)) i++;
        while (cmp(mid,L[j])) j--;
        if (i<=j)
        {
            swap=L[i];
            L[i]=L[j];
            L[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(L,i,r);
    if (l<j) QSort(L,l,j);
}

//判断l1与l2的交点是否在半平面hpl外
int IntersectionOutOfHalfPlane(Line &hpl,Line &l1,Line &l2)
{
     Point p=GetIntersect(l1,l2);
     return (epssgn(Cross(hpl.p1-p,hpl.p2-p))<0);
}

//求n个半平面l的半平面交，得到的交点储存在p中，交点数目返回到pn
void HalfPlaneIntersect(Line l[],int n,Point p[],int &pn)
{
    int i,j;
    int dq[MaxN],top,bot;
    //排序是在满足所有半平面A*x+B*y+C>0或（<,<=,>=）,
    //也就是所有半平面的符号均相同的情况下对极角进行排序。
    QSort(l,0,n-1);
    //极角相同时，只保留最靠里面的那条
    for (i=j=0;i<n;i++) if (epssgn(l[i].angle-l[j].angle)>0) l[++j]=l[i];
    n=j+1;
    dq[0]=0; //双端队列
    dq[1]=1;
    top=1;   //顶部和底部
    bot=0;
    for (i=2;i<n;i++)
    {
        //当栈顶的两条直线交点在当前半平面外部时，弹栈
        while (top>bot && IntersectionOutOfHalfPlane(l[i],l[dq[top]],l[dq[top-1]])) top--;
        //由于求的是一个凸多边形，所以当半平面转过接近一圈时，某个半平面满足上一个while的条件后，
        //它又会影响到底部的两条直线，当底部的两条直线的交点，在当前的半平面外部时，底部弹栈
        while (top>bot && IntersectionOutOfHalfPlane(l[i],l[dq[bot]],l[dq[bot+1]])) bot++;
        dq[++top]=i; //当前半平面入栈
    }
    //当最顶部的两条直线的交点不在最底部的半平面内时，顶部的那个半平面是多余的，顶部弹栈
    while (top>bot && IntersectionOutOfHalfPlane(l[dq[bot]],l[dq[top]],l[dq[top-1]])) top--;
    //当最底部的两条直线的交点不在最顶部的半平面内时，底部的那个半平面是多余的，底部弹栈
    while (top>bot && IntersectionOutOfHalfPlane(l[dq[top]],l[dq[bot]],l[dq[bot+1]])) bot++;
    dq[++top]=dq[bot]; //将最底部的半平面放到最顶部来，方便下面求顶点
    for (pn=0,i=bot;i<top;i++,pn++) p[pn]=GetIntersect(l[dq[i+1]],l[dq[i]]);
}
/*-----半平面交模板-----*/

Line l[MaxN];
Point p[MaxN];
int n,pn;

int main()
{
    int i,t=0;
    double x1,y1,x2,y2;
    freopen("poj1474.txt","r",stdin);
    freopen("poj1474ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y); //注意点给出的是顺时针方向
        for (i=0;i<n;i++) l[i]=Line(p[(i+1)%n],p[i]);      //我们需要的是逆时针方向的
        HalfPlaneIntersect(l,n,p,pn);
        t++;
        printf("Floor #%d\n",t);
        if (pn>2) printf("Surveillance is possible.\n\n");
        else printf("Surveillance is impossible.\n\n");    //半平面交点大于等于3，有核
    }
    return 0;
}
