#include <stdio.h>
#include <math.h>
#define MaxN 1001
#define MaxE 1001*501
#define eps  0.0001

/*---------------Kruskal Template Start---------------*/

struct TEdge
{
    int u,v;
    double h,w,dis;
}edge[MaxE];

int father[MaxN],edgenum;

void InitEdge() 
{
    edgenum=0;
}

void AddEdge(int u,int v,int h,double dis)
{
    edge[edgenum].u=u;
    edge[edgenum].v=v;
    edge[edgenum].dis=dis;
    edge[edgenum].h=h;
    edgenum++;
}

int GetFather(int x)
{
    if (x!=father[x]) father[x]=GetFather(father[x]); //路径合并 
    return father[x];
}

void QSort(int l,int r)
{
    int i=l,j=r;
    double mid;
    struct TEdge swap;
    mid=edge[(l+r)/2].w;
    while (i<=j)
    {
        while (edge[i].w<mid) i++;
        while (edge[j].w>mid) j--;
        if (i<=j)
        {
            swap=edge[i];
            edge[i]=edge[j];
            edge[j]=swap;
            i++;j--;
        }
    }
    if (l<j) QSort(l,j);
    if (i<r) QSort(i,r);
}

double Kruskal(int nodenum)
{
    int cnt=0,i,f1,f2;
    double sumh=0.0,sumd=0.0;
    QSort(0,edgenum-1); 
    for (i=1;i<=nodenum;i++) father[i]=i;  //初始化并查集 
    for (i=0;i<edgenum;i++)
    {
        f1=GetFather(edge[i].u);
        f2=GetFather(edge[i].v);
        if (f1!=f2)
        {
            father[f1]=f2;
            //res+=edge[i].w;
            //下面两行是迭代的处理方式
            sumh+=edge[i].h;     
            sumd+=edge[i].dis;
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    return (sumh/sumd);  //返回新的迭代值 
}

/*---------------Kruskal Template Start---------------*/

struct TVillage
{
    double x,y,h;
}v[MaxN];

int n; 

double dist(int va,int vb)
{
    double dx,dy;
    dx=v[va].x-v[vb].x;
    dy=v[va].y-v[vb].y;
    return sqrt(dx*dx+dy*dy);
}

void RefreshEdge(double mid)
{
    int i;
    for (i=0;i<edgenum;i++) edge[i].w=edge[i].h-mid*edge[i].dis;
}

int main()
{
    int i,j;
    double rate,prerate;
    freopen("poj2728.txt","r",stdin);
    freopen("poj2728ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        InitEdge();
        for (i=1;i<=n;i++)
        {
       	    scanf("%lf %lf %lf",&v[i].x,&v[i].y,&v[i].h);
       	    for (j=1;j<i;j++) AddEdge(i,j,fabs(v[i].h-v[j].h),dist(i,j));
        }
        prerate=0.0;
        rate=1.0;
        while (fabs(rate-prerate)>eps)
        {
       	    prerate=rate;
       	    RefreshEdge(rate);
       	    rate=Kruskal(n);
        }
        printf("%.3f\n",rate);
    }
    return 0;
}
