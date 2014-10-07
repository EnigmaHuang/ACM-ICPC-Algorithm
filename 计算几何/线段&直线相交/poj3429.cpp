#include<stdio.h>
#include<math.h>

#define MaxN 101

struct Rational         //a分母，b分子
{
    long long a,b;
    Rational(long long x=0,long long y=0):a(x),b(y){}
};

struct Point
{
    Rational x,y;
    Point (Rational fz=Rational(0,1),Rational fm=Rational(0,1)):x(fz),y(fm){}
};

typedef Point Vector;

long long gcd(long long a, long long b)   
{
    if (b==0) return a;
    return gcd(b,a%b);
}

long long lcm(long long a, long long b)
{
    return a*b/gcd(a, b);
}

Rational operator + (Rational &a,Rational &b)
{
    long long l=lcm(a.b, b.b);
    Rational res;
    res.a=a.a*l/a.b+b.a*l/b.b;
    res.b=l;
    return res;
}

Rational operator - (Rational &a, Rational &b)
{
    long long l=lcm(a.b, b.b);
    Rational res;
    res.a=a.a*l/a.b-b.a*l/b.b;
    res.b=l;
    return res;
}

Rational operator * (Rational &a, Rational &b)
{
    long long g1,g2;
    g1=gcd(a.b,b.a);
    g2=gcd(a.a,b.b);
    Rational res;
    res.a=a.a/g2*(b.a/g1);
    res.b=a.b/g1*(b.b/g2);
    return res;
}

Rational operator / (Rational &a, Rational &b)
{
    Rational c;
    c.a=b.b;
    c.b=b.a;
    return a*c;
}

int operator == (Rational a,Rational b)
{
    return (a.a==b.a && a.b==b.b);
}

int operator == (Point a,Point b)
{
    return (a.x==b.x && a.y==b.y);
}

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2向量求叉积*/
Rational Cross(Vector a,Vector b)
{
    Rational r1=a.x*b.y;
    Rational r2=b.x*a.y;
    return r1-r2;
}

Point GetIntersect(Point &p1,Point &p2,Point &p3,Point &p4)
{
    Rational a11 = p2.y-p1.y;
    Rational a12 = p1.x-p2.x;
    Rational a21 = p4.y-p3.y;
    Rational a22 = p3.x-p4.x;
    Rational b11 = p1.x*p2.y;
    Rational b12 = p2.x*p1.y;
    Rational b21 = p3.x*p4.y;
    Rational b22 = p4.x*p3.y;
    Rational b1  = b11-b12;
    Rational b2  = b21-b22;
    Rational fz1 = Cross(Point(b1,a12),Point(b2,a22));
    Rational fz2 = Cross(Point(a11,b1),Point(a12,b2));
    Rational fm  = Cross(Point(a11,a12),Point(a21,a22));
    return Point(fz1/fm,fz2/fm);
}

Point p[MaxN];

int main()
{
    int n,m,i,j,s1,e1,s2,e2,flag,ans;
    double x,y;
    freopen("poj3429.txt","r",stdin);
    freopen("poj3429ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=1;i<=n;i++)
        {
            scanf("%lf%lf",&x,&y);
            p[i].x.a=x;
            p[i].x.b=1;
            p[i].y.a=y;
            p[i].y.b=1;
        }
        scanf("%d",&m);
        ans=0;
        for (i=0;i<m;i++)
        {
             scanf("%d%d%d%d",&s1,&e1,&s2,&e2);
             Point its=GetIntersect(p[s1],p[e1],p[s2],p[e2]);
             flag=1;
             for (j=0;j<n;j++) if (its==p[j])
             {
                 flag=0;
                 break;
             }
             if (flag) p[++n]=its;
             if (ans==0 && its.x.a==0 && its.y.a==0) ans=i+1;
        }
        printf("%d\n",ans);
    }
}
