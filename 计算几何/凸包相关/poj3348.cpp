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

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2向量求叉积，同时也可以求面积 */
inline double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
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

Point p[MaxN];
int res[MaxN];

int main()
{
    int n,i,chnum;
    double s;
    freopen("poj3348.txt","r",stdin);
    freopen("poj3348ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        if (n<3)
        {
	    printf("0\n");
	    continue;
        }
        chnum=Graham(p,n,res);
        s=0;
	for (i=0;i<chnum;i++) s+=Cross(p[res[i]]-p[res[0]],p[res[i+1]]-p[res[0]])/2;
	printf("%d\n",(int)(s/50));
    }
    return 0;
}
