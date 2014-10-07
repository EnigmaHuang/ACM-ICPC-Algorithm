#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define MaxN 51

struct Point
{
    double x,y;
    int id,order; 
    Point(double a=0,double b=0){x=a;y=b;} 
};

/*
得到sp-op和ep-op的叉积
>0时ep在opsp的逆时针方向，<0时顺时针，=0时共线 
*/ 
double Cross(Point &sp,Point &ep,Point &op) 
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

double dist(Point &p1,Point &p2)
{
    double a=p1.x-p2.x;
    double b=p1.y-p2.y;
    return sqrt(a*a+b*b);
}

Point p[MaxN];
int n;

void DFS(int prev,int depth)
{
    int i,min=0;
    double w;
    if (depth==n) return ;
    while (p[min].order!=-1) min++; //选一个还没用过的点作为当前解 
    for (i=min+1;i<n;i++)
    {
        if (p[i].order!=-1) continue; 
        w=Cross(p[min],p[i],p[prev]);
        if (w<-eps) min=i;  //如果新的点在当前点的顺时针方向，则用新的点，否则要距离更短才用 
        else if (abs(w)<eps && dist(p[prev],p[i])<dist(p[prev],p[min])) min=i;
    }
    p[min].order=depth;
    DFS(min,depth+1);
}

void QSort(int l,int r)
{
    int i=l,j=r,mid;
    Point swap;
    mid=p[(i+j)/2].order;
    while (i<=j)
    {
        while (p[i].order<mid) i++;
        while (p[j].order>mid) j--;
        if (i<=j)
        {
       	    swap=p[i];
       	    p[i]=p[j];
       	    p[j]=swap;
       	    i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int main()
{
    int i,min,t;
    freopen("poj1696.txt","r",stdin);
    freopen("poj1696ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        min=0;
        for (i=0;i<n;i++)
        {
       	    scanf("%d%lf%lf",&p[i].id,&p[i].x,&p[i].y);
       	    p[i].order=-1;
   	    if (p[i].y<p[min].y) min=i;
        }
        p[min].order=0;
        DFS(min,1);
        QSort(0,n-1);
        printf("%d",n);
        for (i=0;i<n;i++) printf(" %d",p[i].id);
        printf("\n");
    }
    return 0;
}
