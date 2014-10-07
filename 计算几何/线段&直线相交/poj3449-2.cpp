#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define MaxN 32 
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

typedef Point Vector;

struct Polygon //非模板数据类型，注意 
{
    int sides,itsnum;         //边数，相交数 
    char name,itsname[MaxN];  //编号，相交对象编号 
    Point p[MaxN];
};


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

Polygon a[MaxN];

//已知正方形对角坐标，补完正方形 
void FinishSqu(Polygon &src)
{
    src.sides=4;
    src.p[2]=src.p[1]; //先移开
    src.p[1].x=(src.p[0].x+src.p[2].x+src.p[2].y-src.p[0].y)/2;
    src.p[1].y=(src.p[0].y+src.p[2].y+src.p[0].x-src.p[2].x)/2;
    src.p[3].x=(src.p[0].x+src.p[2].x-src.p[2].y+src.p[0].y)/2;
    src.p[3].y=(src.p[0].y+src.p[2].y-src.p[0].x+src.p[2].x)/2; 
}

//已知长方形三点坐标，补完长方形 
void FinishRect(Polygon &src)
{
    src.sides=4;
    src.p[3].x=src.p[2].x-src.p[1].x+src.p[0].x;
    src.p[3].y=src.p[2].y-src.p[1].y+src.p[0].y;    
}

void QSort(int l,int r)
{
    int i=l,j=r;
    char mid=a[(i+j)/2].name;
    Polygon swap;
    while (i<=j)
    {
        while (a[i].name<mid) i++;
        while (a[j].name>mid) j--;
        if (i<=j)
        {
                   swap=a[i];
                   a[i]=a[j];
                   a[j]=swap;
                   i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int PolygonIntersect(Polygon &a,Polygon &b)
{
    int i,j;
    for (i=0;i<a.sides;i++) //两两枚举边判断相交 
        for (j=0;j<b.sides;j++)
            if (IsIntersect
                (a.p[i],a.p[(i+1)%a.sides],
                 b.p[j],b.p[(j+1)%b.sides])
               ) return 1;
    return 0;
}

int main()
{
    int n,i,j;
    char s[255];
    freopen("poj3449.txt","r",stdin);
    freopen("poj3449ans.txt","w",stdout);
    while (1)
    {
        n=0;
        while (1)
        {
                   scanf("%s",s);
                   if (s[0]=='.' || s[0]=='-') break;
                   a[n].name=s[0];
                   scanf("%s",s);
                   if (s[0]=='l' || s[0]=='s') a[n].sides=2;
                   else if (s[0]=='r' || s[0]=='t') a[n].sides=3;
                   else scanf("%d",&a[n].sides);
                   for (j=0;j<a[n].sides;j++) scanf(" (%lf,%lf)", &a[n].p[j].x,&a[n].p[j].y);
                   if (s[0]=='s') FinishSqu(a[n]);
            else if (s[0]=='r') FinishRect(a[n]);
            a[n].itsnum=0;
            n++;
        }
        if (s[0]=='.') break;
        
        QSort(0,n-1);     //按编号排序一下方便输出 
        for (i=0;i<n;i++) //两两枚举多边形判断相交 
            for (j=i+1;j<n;j++)
            {
                       if (!PolygonIntersect(a[i],a[j])) continue;
                       a[i].itsname[a[i].itsnum++]=a[j].name;
                       a[j].itsname[a[j].itsnum++]=a[i].name;
            }
        
         for (i=0;i<n;i++)
        {
            printf("%c ",a[i].name);
            if (a[i].itsnum==0) 
            {
                printf("has no intersections\n"); 
                continue;
            }
            printf("intersects with ");
            if (a[i].itsnum==1) printf("%c\n",a[i].itsname[0]);
            else if (a[i].itsnum==2) printf("%c and %c\n",a[i].itsname[0],a[i].itsname[1]);
            else 
            {
                for (j=0;j<a[i].itsnum-1;j++) printf("%c, ",a[i].itsname[j]);
                printf("and %c\n",a[i].itsname[j]);
            }
        }
        printf("\n");
    }
    return 0;
}
