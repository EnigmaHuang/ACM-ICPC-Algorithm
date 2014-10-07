#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps 0.00000001
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define MaxN 100005
#define MaxQ 1005 

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

struct Segment
{
    Point s,e;
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

Segment seg[MaxN];
int ans[MaxQ];

void QSort(int l,int r)
{
    int i=l,j=r,mid,swap;
    mid=ans[(l+r)/2];
    while (i<=j)
    {
        while (ans[i]<mid) i++;
        while (ans[j]>mid) j--;
        if (i<=j)
        {
            swap=ans[i];
            ans[i]=ans[j];
            ans[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int main()
{
    int n,m,i,j,pos;
    freopen("poj2653.txt","r",stdin);
    freopen("poj2653ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        m=0;
        memset(ans,-1,sizeof(ans));
        for (i=1;i<=n;i++)
        {
                   scanf("%lf%lf%lf%lf",&seg[i].s.x,&seg[i].s.y,&seg[i].e.x,&seg[i].e.y);
                   pos=-1;
                   for (j=0;j<m;j++)
                   {
                       if (ans[j]==-1) pos=j;  //看这个位置最上面当前有无线段，无则记录，有则到下面一行判断相交
                       else if (IsIntersect(seg[i].s,seg[i].e,seg[ans[j]].s,seg[ans[j]].e)) ans[j]=-1;  //相交了，清零
                   }
                   if (pos==-1) ans[m++]=i;  //全部不相交，新加一段
                   else ans[pos]=i; //补上中间的空洞
        }
        QSort(0,m-1);
        for (i=0;ans[i]==-1;i++);
        printf("Top sticks:");
        while (i<m-1) printf(" %d,",ans[i++]);
        printf(" %d.\n",ans[i]);
    }
    return 0;
}
