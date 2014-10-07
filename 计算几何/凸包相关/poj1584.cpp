#include<stdio.h>
#include<math.h>

#define eps 1e-8
#define MaxN 201

//二维点类
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

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

//求点C到线段AB的距离
double PointToSegDist(Point A,Point B,Point C)
{
    if (dis(A,B)<eps) return dis(B,C);
    if (epssgn(Dot(B-A,C-A))<0) return dis(A,C);
    if (epssgn(Dot(A-B,C-B))<0) return dis(B,C);
    return fabs(Cross(B-A,C-A))/dis(B,A);
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

Point p[MaxN];
int   res[MaxN];
int   chnum;

struct Circle
{
    Point center;
    double r;
}cir;

int main()
{
    int n,i,j,k,flag;
    double direct,tmp;
    freopen("poj1584.txt","r",stdin);
    freopen("poj1584ans.txt","w",stdout);
    while (scanf("%d",&n) && n>=3)
    {
        scanf("%lf%lf%lf",&cir.r,&cir.center.x,&cir.center.y);
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        for (i=0;i<n-2;i++)  //先确定一开始的方向是顺时针还是逆时针
        {
            direct=Cross(p[i+1],p[i+2],p[i]);
            if (epssgn(direct)!=0) break;
        }
        flag=1;
	for (i;i<n-2;i++)  //继续向后比较，如果有反向的那么就退出
        {
            tmp=Cross(p[i+1],p[i+2],p[i]);
	    if (epssgn(tmp*direct)<0)
	    {
                flag=0;
                break;
	    }
        }
        if (!flag)
        {
	    printf("HOLE IS ILL-FORMED\n");
	    continue;
        }
        //如果direct>0表示是逆时针点集，否则是顺时针，重新构筑一下方便调用函数
	if (direct>0) for (i=0;i<n;i++) res[i]=i;
	else for (i=0;i<n;i++) res[i]=n-i-1;
	chnum=n;
        if (!PointInConvexHull(p,res,chnum,cir.center))
        {
            printf("PEG WILL NOT FIT\n");
            continue;
        }
        //对比圆心和每一条边的距离
        flag=1;
        for (i=0;i<n;i++) if (cir.r>PointToSegDist(p[i],p[(i+1)%n],cir.center))
        {
            printf("PEG WILL NOT FIT\n");
            flag=0;
            break;
        }
        if (flag) printf("PEG WILL FIT\n");
    }
    return 0;
}
