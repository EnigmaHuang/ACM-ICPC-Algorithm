#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps  1e-7
#define MaxN 51

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

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
int vis[MaxN];
int chnum;

int main()
{
    int i,start,n=0;
    freopen("poj2007.txt","r",stdin);
    freopen("poj2007ans.txt","w",stdout);
    while (scanf("%lf%lf",&p[n].x,&p[n].y)!=EOF) n++;
    chnum=Graham(p,n,res);
    for (start=0;start<chnum;start++) if(!p[res[start]].x && !p[res[start]].y) break;
    for (i=start;i<chnum;i++) printf("(%.f,%.f)\n", p[res[i]].x, p[res[i]].y);
    for (i=0;i<start;i++) printf("(%.f,%.f)\n", p[res[i]].x, p[res[i]].y);
    return 0;
}
