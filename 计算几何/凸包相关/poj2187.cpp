#include<stdio.h>
#include<math.h>

#define eps  1e-7
#define MaxN 50001

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

//两向量求叉积，求三角形面积需要除以2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
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
        //卡住i，若向前旋转j能令面积更大的话就一直转一下去 
        while (Cross(p[res[i]]-p[res[i+1]],p[res[j+1]]-p[res[i+1]])
              <Cross(p[res[i]]-p[res[i+1]],p[res[j]]  -p[res[i+1]])) 
              j=(j+1)%chnum; 
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
/*------Graham求凸包----*/

Point p[MaxN];
int   res[MaxN];
int   chnum;
int   app[MaxN][2];

int main()
{
    int i,n,appnum;
    double ans;
    freopen("poj2187.txt","r",stdin);
    freopen("poj2187ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        if (n<3) printf("%.f\n",dis(p[0],p[1])*dis(p[0],p[1]));
        else
        {
            chnum=Graham(p,n,res);
            ans=Diameter(p,res,chnum,app,appnum);
            /*旋转卡壳用的调试信息
            for (i=0;i<chnum;i++) fprintf(stderr,"%.2f %.2f\n",p[res[i]].x,p[res[i]].y);
            for (i=0;i<appnum;i++) 
            {
                fprintf(stderr,"APP : (%.2f %.2f)",p[app[i][0]].x,p[app[i][0]].y);
                fprintf(stderr,"-- (%.2f %.2f)",p[app[i][1]].x,p[app[i][1]].y);
                fprintf(stderr," \t dist=%.2f\n",dis(p[app[i][0]],p[app[i][1]]));
            }
            */
            /*暴力写法
            ans=0;
            for (i=0;i<chnum-1;i++)
                for (j=i+1;j<chnum;j++)
                    ans=max(ans,dis(p[res[i]],p[res[j]]));
            */
            printf("%.f\n",ans*ans);
        }
    }
    return 0;
}
