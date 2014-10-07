#include<stdio.h>
#include<math.h>
#include<string.h>

#define MaxN 1000005
#define eps  1e-8

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

const int way[9][2] = {{-1,-1},{0,-1},{1,-1},{-1,0},{0,0},{1,0},{-1,1},{0,1},{1,1}};

typedef Point Vector;

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

//采用eps的精度判断大/小于零
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

/* 2向量求叉积，同时也可以求面积 */
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

int main()
{
    int t,n,i,len;
    char c,str[MaxN];
    double res;
    long long ans;
    Point p0(0,0),p1,p2;
    freopen("poj1654.txt","r",stdin);
    freopen("poj1654ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%c%s",&c,str);
        len=strlen(str);
        if (len<=3)
        {
            printf("0\n");
            continue;
        }
        p1.x=p0.x+way[str[0]-'1'][0];
        p1.y=p0.y+way[str[0]-'1'][1];
        res=0;
        for (i=1;i<len-1;i++)
        {
            p2.x=p1.x+way[str[i]-'1'][0];
            p2.y=p1.y+way[str[i]-'1'][1];
            res+=Cross(p1,p2);
            p1=p2;
        }
        getchar();
        if (epssgn(res)<0) res=-res;
        ans=(long long )res;
        if (ans&1) printf("%lld.5\n",ans/2);
        else printf("%lld\n",ans/2);
    }
    return 0;
}
