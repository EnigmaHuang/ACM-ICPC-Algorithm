#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps 1e-8
#define pi  3.141592653589793

using namespace std;

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

//二维线段类
struct Segment
{
    Point s,e;
    Segment(Point a,Point b){s=a;e=b;}
    Segment(double x1,double y1,double x2,double y2)
    {
        s=Point(x1,y1);
        e=Point(x2,y2);
    }
    Segment(){}
};

//向量的加减及数乘
Vector operator + (Point a,Point b)
{
    return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

Vector operator * (Point a,double k)
{
    return Vector(a.x*k,a.y*k);
}

Vector operator / (Point a,double k)
{
    return Vector(a.x/k,a.y/k);
}

//求向量的模（长度）
double len(Vector a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}

//得到sp-op和ep-op的叉积
//>0时ep在opsp的逆时针方向，<0时顺时针，=0时共线
double Cross(Point &sp, Point &ep, Point &op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

//两向量求叉积，求三角形面积需要除以2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//两向量求点积
double Dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
}

//求最大最小值
double max(double a,double b)
{
    if (a<b) return b; else return a;
}

double min(double a,double b)
{
    if (a>b) return b; else return a;
}

//采用eps的精度判断大/小于零
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//求两点之间的直线距离
double dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

//判断两直线是否平行
int Parallel(Line l1,Line l2)
{
    return (fabs(l1.a*l2.b-l2.a*l1.b)<eps);
}

//判断两直线是否相等
int LineEqual(Line l1,Line l2)
{
    if (!Parallel(l1,l2)) return 0;
    else return (fabs(l1.a*l2.c-l2.a*l1.c)<eps && fabs(l1.b*l2.c-l2.b*l1.c)<eps);
}

//求点C到线段AB的距离 
double PointToSegDist(Point A,Point B,Point C)
{
    if (dis(A,B)<eps) return dis(B,C);
    if (epssgn(Dot(B-A,C-A))<0) return dis(A,C);
    if (epssgn(Dot(A-B,C-B))<0) return dis(B,C);
    return fabs(Cross(B-A,C-A))/dis(B,A);
}

//求线段两端AB到另一线段CD的距离
double TwoSegMinDist(Point A,Point B,Point C,Point D)
{
    return min(min(PointToSegDist(A,B,C),PointToSegDist(A,B,D)),
               min(PointToSegDist(C,D,A),PointToSegDist(C,D,B)));
}

Point SymPoint(Point p,Line l) //求二维平面上点p关于直线p1p2的对称点
{
    Point result;
    double a=l.p2.x-l.p1.x;
    double b=l.p2.y-l.p1.y;
    double t=((p.x-l.p1.x)*a+(p.y-l.p1.y)*b)/(a*a+b*b);
    result.x=2*l.p1.x+2*a*t-p.x;
    result.y=2*l.p1.y+2*b*t-p.y;
    return result;
}

//判断线段s1e1与s2e2是否相交（含端点）
//不含端点的话将下面的<=改成<
int IsSegmentIntersect(Point s1, Point e1, Point s2, Point e2)
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

//知道直线上两点p1p2，判断直线与线段se是否相交，含顶点
int IsLineIntersectSegment(Point p1,Point p2,Point s,Point e)
{
    if (Cross(p1,p2,s)*Cross(p1,p2,e)>eps) return 0;
    else return 1;
}

int IsLineIntersectSegment(Line l1,Point s,Point e)
{
    if (Cross(l1.p1,l1.p2,s)*Cross(l1.p1,l1.p2,e)>eps) return 0;
    else return 1;
}

//求两条直线l1和l2的交点
Point GetIntersect(Line l1, Line l2) 
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

//求质量均匀分布的多边形的重心
Point BaryCenter(Point *p,int n)
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

//求多边形面积，要求点集按逆时针顺序
double ConvexPolygonArea(Point *p,int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

//求以原点为圆心，过a、b，半径为r的扇形面积
double SectorArea(Point a,Point b,double r)
{
    double theta=atan2(a.y,a.x)-atan2(b.y,b.x);
    while (theta<=0) theta+=2*pi;
    while (theta>=2*pi) theta-=2*pi;
    theta=min(theta,2*pi-theta);
    return r*r*theta/2;
}

//求以o为圆心r为半径的圆与线段（直线）ab的交点
//返回的ret是交点，num是交点数量
//把判断t范围的两个if去掉可以计算圆与直线的交点
void CircleCrossLine(Point a,Point b,Point o,double r,Point ret[],int &num)
{
    double x0=o.x,y0=o.y;
    double x1=a.x,y1=a.y;
    double x2=b.x,y2=b.y;
    double dx=x2-x1,dy=y2-y1;
    double A=dx*dx+dy*dy;
    double B=2*dx*(x1-x0)+2*dy*(y1-y0);
    double C=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
    double delta=B*B-4*A*C;
    num=0;
    if (epssgn(delta)>=0)
    {
        double t1=(-B-sqrt(fabs(delta)))/(2*A);
        double t2=(-B+sqrt(fabs(delta)))/(2*A);
        if (epssgn(t1-1.0)<=0 && epssgn(t1)>=0)
            ret[num++]=Point(x1+t1*dx,y1+t1*dy);
        if (epssgn(t2-1.0)<=0 && epssgn(t2)>=0)
            ret[num++]=Point(x1+t2*dx,y1+t2*dy);
    }
}

//求以原点为圆心半径为r的园，与原点、a、b组成的三角形的重叠面积
double Calc(Point a,Point b,double r)
{
    Point p[2];
    int num=0;
    int ina=(epssgn(len(a)-r)<0);
    int inb=(epssgn(len(b)-r)<0);
    if (ina)
    {
        if (inb) return fabs(Cross(a,b))/2.0; //情形1：三角形完全在圆内：直接求三角形面积
        else  //情形2：一个点在圆内，一个点在圆外：分割成一个完全在圆内的三角形和一个扇形
        {
            CircleCrossLine(a,b,Point(0,0),r,p,num);
            return SectorArea(b,p[0],r)+fabs(Cross(a,p[0]))/2.0;
        }
    }
    else
    {
        CircleCrossLine(a,b,Point(0,0),r,p,num);
        //情形2：一个点在圆内，一个点在圆外：分割成一个完全在圆内的三角形和一个扇形
        if (inb) return SectorArea(p[0],a,r)+fabs(Cross(p[0],b))/2.0;
        else
        {
            //情形4：两个点都在圆外，但是两点的连线与圆有两个焦点：分割成一个完全在圆内的三角形和两个扇形
            if (num==2) return SectorArea(a,p[0],r)+SectorArea(p[1],b,r)+fabs(Cross(p[0],p[1]))/2.0;
            //情形3：两个点都在圆外，并且相交处为一个扇形：直接求扇形面积
            else return SectorArea(a,b,r);
        }
    }
}

//求质量均匀分布的三角形的重心
Point TriangleMassCenter(Point a,Point b,Point c)
{
    return (a+b+c)/3.0;
}

//求三角形的外心
Point TriangleCircumCenter(Point a,Point b,Point c)
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

//求三角形的垂心
Point TriangleOrthoCenter(Point a,Point b,Point c)
{
    return TriangleMassCenter(a,b,c)*3.0-TriangleCircumCenter(a,b,c)*2.0;
}

//求三角形的内心
Point TriangleInnerCenter(Point a,Point b,Point c)
{
    Point res;
    double la=len(b-c);
    double lb=len(a-c);
    double lc=len(a-b);
    res.x=(la*a.x+lb*b.x+lc*c.x)/(la+lb+lc);
    res.y=(la*a.y+lb*b.y+lc*c.y)/(la+lb+lc);
}

/*------Graham求凸包----*/
int cmp(Point &a,Point &b)
{
    if (a.y==b.y) return (a.x<b.x);
    return (a.y<b.y);
}

//对所有的点进行一次排序
void QSort(Point p[],int l,int r)
{
    int i=l,j=r;
    Point mid=p[(l+r)/2],swap;
    while (i<=j)
    {
        while (cmp(p[i],mid)) i++;
        while (cmp(mid,p[j])) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

//n为原图的点数，p[]为原图的点（0~n-1），top为凸包点的数量（0~top-1），res[]为凸包点的下标，。
int Graham(Point p[],int n,int res[])
{
    int i,len,top;
    top=1;
    QSort(p,0,n-1);
    for (i=0;i<3;i++) res[i]=i;
    for (i=2;i<n;i++)
    {
        while (top && epssgn(Cross(p[i],p[res[top]],p[res[top-1]]))>=0) top--;
        res[++top]=i;
    }
    len=top;
    res[++top]=n-2;
    for (i=n-3;i>=0;i--)
    {
        while (top!=len && epssgn(Cross(p[i], p[res[top]], p[res[top-1]]))>=0) top--;
        res[++top]=i;
    }
    return top;
}

//判断点x是否在凸包p[res[1~chnum]]中，返回1则为在内部或边界上
int PointInConvexHull(Point p[],int res[],int chnum,Point x)
{
    //找一个凸包内的点
    Point g=(p[res[0]]+p[res[chnum/3]]+p[res[2*chnum/3]])/3.0;
    int l=0,r=chnum,mid;
    //二分凸包
    while (l+1<r)
    {
        mid=(l+r)/2;
        if (epssgn(Cross(p[res[l]]-g,p[res[mid]]-g))>0)
        {
            if (epssgn(Cross(p[res[l]]-g,x-g))>=0
             && epssgn(Cross(p[res[mid]]-g,x-g))<0) r=mid;
            else l=mid;
        }
        else
        {
            if (epssgn(Cross(p[res[l]]-g,x-g))<0
             && epssgn(Cross(p[res[mid]]-g,x-g))>=0) l=mid;
            else r=mid;
        }
    }
    r%=chnum;
    if (epssgn(Cross(p[res[r]]-x,p[res[l]]-x))==-1) return 1; else return 0;
}

//旋转卡壳求凸包p[res[1~chnum]]的直径，对踵点数量appnum，存储在app[][2]中 
double Diameter(Point p[],int res[],int chnum,int app[][2],int &appnum) //AntiPodal Point
{
    int i,j;
    double ret=0,nowlen;
    res[chnum]=res[0];
    j=1;
    appnum=0;
    for (i=0;i<chnum;i++)
    {
        while (Cross(p[res[i]]-p[res[i+1]],p[res[j+1]]-p[res[i+1]])
              <Cross(p[res[i]]-p[res[i+1]],p[res[j]]-p[res[i+1]])) 
        {
            j++;
            j%=chnum;
        }
        app[appnum][0]=res[i];
        app[appnum][1]=res[j];
        appnum++;
        nowlen=dis(p[res[i]],p[res[j]]);
        if (nowlen>ret) ret=nowlen;
        nowlen=dis(p[res[i+1]],p[res[j+1]]);
        if (nowlen>ret) ret=nowlen;
    }
    return ret;
}

//旋转卡壳求凸包p[res[1~chnum]]内最大面积三角形
double ConvexHullMaxTriangleArea(Point p[],int res[],int chnum) 
{
    int i,j,k;
    double area=0,tmp;
    k=2;j=1;
    res[chnum]=res[0];
    for (i=0;i<chnum;i++)
    {
        //卡住i,j，若向前旋转k能令面积更大的话就一直转一下去 
        while (fabs(Cross(p[res[j]]-p[res[i]],p[res[(k+1)%chnum]]-p[res[i]]))
              >fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]          -p[res[i]])))
              k=(k+1)%chnum;
        tmp=fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]]));
        if (tmp>area) area=tmp;
        //卡住i,k，若向前旋转j能令面积更大的话就一直转一下去 
        while (fabs(Cross(p[res[(j+1)%chnum]]-p[res[i]],p[res[k]]-p[res[i]]))
              >fabs(Cross(p[res[j]]-          p[res[i]],p[res[k]]-p[res[i]])))
              j=(j+1)%chnum;
        tmp=fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]]));
        if (tmp>area) area=tmp;
                //j,k转到最大位置，向前转i(i++)
    }
    return area/2;
}

//求两凸包p、q间的最小距离，注意调用的时候要交换参数位置调用两次
//卡住p（p步进），旋转q，求能得到的最小距离 
double TwoConvexHullMinDist(Point P[],Point Q[],int n,int m)
{
    int YMinP=0,YMaxQ=0,i;
    double tmp,ans=999999999;
    for (i=0;i<n;i++) if (P[i].y<P[YMinP].y) YMinP=i;
    for (i=0;i<m;i++) if (Q[i].y>Q[YMaxQ].y) YMaxQ=i;
    P[n]=P[0];
    Q[m]=Q[0];
    for (i=0;i<n;i++)
    {
        //注意，tmp保存的是>比较的结果 
        while (tmp=Cross(Q[YMaxQ+1]-P[YMinP+1],P[YMinP]-P[YMinP+1])
                  >Cross(Q[YMaxQ]  -P[YMinP+1],P[YMinP]-P[YMinP+1]))
              YMaxQ=(YMaxQ+1)%m;
        if (tmp<0) ans=min(ans,PointToSegDist(P[YMinP],P[YMinP+1],Q[YMaxQ]));
        else       ans=min(ans,TwoSegMinDist (P[YMinP],P[YMinP+1],Q[YMaxQ],Q[YMaxQ+1]));
        YMinP=(YMinP+1)%n;
    }
    return ans;
}
/*------Graham求凸包----*/

/*-----半平面交O(nlogn)模板-----*/
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

//半平面hpl向内推进dis长度
Line HalfPlaneMoveIn(Line &hpl,double &dis)
{
    double dx=hpl.p1.x-hpl.p2.x;
    double dy=hpl.p1.y-hpl.p2.y;
    double ll=len(hpl.p1-hpl.p2);
    Point pa=Point(dis*dy/ll+hpl.p1.x,hpl.p1.y-dis*dx/ll);
    Point pb=Point(dis*dy/ll+hpl.p2.x,hpl.p2.y-dis*dx/ll);
    return Line(pa,pb);
}

//求n个半平面l的半平面交，得到的交点储存在p中，交点数目返回到pn
//可以将一个多边形每一条边看成半平面，求出来的交就是多边形的核，要求pn>=3
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
/*-----半平面交O(nlogn)模板-----*/

/*-----半平面交O(n^2)模板-----*/
//p是现在切出来的半平面的点，pn是点的数量，需要按顺时针或者逆时针排序
//新的半平面直线为ax+by+c=0
void HalfPlaneCut(Point p[],int &pn,double a,double b,double c)
{
    int cnt=0,i;
    Point tp[MaxN];  //temp_p
    //现在交出来的点在新的半平面内，保留
    for (i=1;i<=pn;i++) if (epssgn(a*p[i].x+b*p[i].y+c)>=0) tp[++cnt]=p[i];
    else //否则如果其前后的点在半平面内，重新切割
    {
        if (epssgn(a*p[i-1].x+b*p[i-1].y+c)>0)
            tp[++cnt]=GetIntersect(Line(p[i-1],p[i]),Line(a,b,c));
        if (epssgn(a*p[i+1].x+b*p[i+1].y+c)>0)
            tp[++cnt]=GetIntersect(Line(p[i],p[i+1]),Line(a,b,c));
    }
    pn=cnt;
    for (i=1;i<=cnt;i++) p[i]=tp[i];
    p[0]=p[cnt];
    p[cnt+1]=p[1];
}
/*-----半平面交O(n^2)模板-----*/
