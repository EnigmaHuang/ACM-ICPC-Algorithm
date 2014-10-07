#include<stdio.h>
#include<math.h>

#define eps  1e-7
#define MaxN 10001

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


inline double dis(Point &a,Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

/*------Graham求凸包----*/
/*
得到sp-op和ep-op的叉积
>0时ep在opsp的逆时针方向，<0时顺时针，=0时共线
*/
inline double Cross(Point sp,Point ep,Point op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

inline int cmp(Point &a,Point &b)
{
    if (a.y==b.y) return (a.x<b.x);
    return (a.y<b.y);
}

//采用eps的精度判断大/小于零
inline int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
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

/*------Graham求凸包----*/

//求向量的模（长度）
double len(Vector a)
{
    return sqrt(a.x*a.x+a.y*a.y);
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

Point p0[MaxN],p[MaxN],q[MaxN];
int   res[MaxN];

double min(double a,double b)
{
    if (a>b) return b; else return a;
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

int main()
{
    int i,n,m;
    double ans,tmp;
    freopen("poj3608.txt","r",stdin);
    freopen("poj3608ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (n==0 && m==0) break;
        //处理一下重新保存，免得后面写起来太麻烦 
        for (i=0;i<n;i++) scanf("%lf%lf",&p0[i].x,&p0[i].y);
        n=Graham(p0,n,res);
        for (i=0;i<n;i++) p[i]=p0[res[i]];
        
        for (i=0;i<m;i++) scanf("%lf%lf",&p0[i].x,&p0[i].y);
        m=Graham(p0,m,res);
        for (i=0;i<m;i++) q[i]=p0[res[i]];
        
        ans=99999999.0;
        //p步进（卡住p），转q 
        tmp=TwoConvexHullMinDist(p,q,n,m);
        if (tmp<ans) ans=tmp;
        //q步进（卡住q），转p 
        tmp=TwoConvexHullMinDist(q,p,m,n);
        if (tmp<ans) ans=tmp;
        printf("%.5f\n",ans);
    }
    return 0;
}
