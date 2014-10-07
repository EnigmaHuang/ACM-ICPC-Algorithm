#include<stdio.h>
#include<math.h>
#include<string.h>
#include<queue>
using namespace std;
#define eps 0.00000001
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define MaxN 105
#define MaxE 10005
#define INF 9999999.0

/*---------------SPFA Template Start---------------*/

struct TEdge
{
    int u,v,next;
    double w;
}edge[MaxE];

int head[MaxN],vistime[MaxN],inqueue[MaxN];
double dist[MaxN];

int index,nodenum;

void AddEdge(int src,int trg,double weight)
{
    edge[index].u=src;
    edge[index].v=trg;
    edge[index].w=weight;
    edge[index].next=head[src];
    head[src]=index++;
}

void InitEdge(int n)
{
    index=1;
    memset(head,-1,sizeof(head));
    nodenum=n;
}

double SPFA(int source,int target)
{
    int i,u,v;
    queue<int> q;
    for (i=0;i<MaxN;i++) dist[i]=INF;
    memset(vistime,0,sizeof(vistime));
    memset(inqueue,0,sizeof(inqueue));
    q.push(source);
    dist[source]=0;
    vistime[source]=1;
    inqueue[source]=1;

    while (!q.empty())
    {
        u=q.front();
        q.pop();
        inqueue[u]=0;
        for (i=head[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].v;
            if (dist[v]>dist[u]+edge[i].w)
            {
                dist[v]=dist[u]+edge[i].w;
                if (!inqueue[v])
                {
                    inqueue[v]=1;
                    q.push(v);
                    //if (++vistime[v]>nodenum) return 0; //有一个点进队超过点数次说明有负环
                }
            }
        }
    }
    //return 1;
    return dist[target];
}

/*---------------SPFA Template Over---------------*/

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

struct Wall
{
    Point v[6];
}wall[20];

Point p[MaxN];

struct Line //ax+by+c=0
{
    double a,b,c;
    Line(Point &p1,Point &p2)
    {
        a=p1.y-p2.y;
        b=p2.x-p1.x;
        c=p1.x*p2.y-p2.x*p1.y;
    }
};

int Parallel(Line &l1,Line &l2)
{
    return (fabs(l1.a*l2.b-l2.a*l1.b)<eps);
}

int LineEqual(Line &l1,Line &l2)
{
    if (!Parallel(l1,l2)) return 0;
    else return (fabs(l1.a*l2.c-l2.a*l1.c)<eps && fabs(l1.b*l2.c-l2.b*l1.c)<eps);
}

int n,m;

double Cross(Point &sp, Point &ep, Point &op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

int IsIntersect(Point &s1, Point &e1, Point &s2, Point &e2)
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


double dis(Point &a,Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int IsLink(int a,int b)
{
    int i;
    if (b==0) i=0; else i=(b-1)/4+1;  //从距离出发点较近的点所在的墙开始搜
    while (i<(a-1)/4)  //到当前点的墙为止
    {
        //下面的两句不要也无所谓，因为即使有边是同一堵墙中间的肯定也不会去走
        //Line l1(p[a],p[b]),l2(wall[i].v[0],wall[i].v[1]);
        //if (LineEqual(l1,l2)) return 0;
        if (IsIntersect(p[a],p[b],wall[i].v[0],wall[i].v[1])) return 0;
        if (IsIntersect(p[a],p[b],wall[i].v[2],wall[i].v[3])) return 0;
        if (IsIntersect(p[a],p[b],wall[i].v[4],wall[i].v[5])) return 0;
        i++;
    }
    return 1;
}

int main()
{
    int i,j,k;
    double x;
    freopen("poj1556.txt","r",stdin);
    freopen("poj1556ans.txt","w",stdout);
    while (scanf("%d",&m)!=EOF)
    {
        if (m==-1) break;
        n=4*m+1;
        p[0].x=0;
        p[0].y=5;
        p[n].x=10;
        p[n].y=5;
        k=1;
        for (i=0;i<m;i++)
        {
            scanf("%lf",&x);
            wall[i].v[0].x=x;
            wall[i].v[5].x=x;
            wall[i].v[0].y=0;
            wall[i].v[5].y=10;
            for (j=1;j<=4;j++)
            {
                p[k].x=x;
                scanf("%lf",&p[k].y);
                wall[i].v[j].x=p[k].x;
                wall[i].v[j].y=p[k].y;
                k++;
            }
        }
        InitEdge(n);
        for (i=1;i<=n;i++)
            for (j=0;j<i;j++)
                if (IsLink(i,j))
                {
                    AddEdge(j,i,dis(p[i],p[j]));
                    AddEdge(i,j,dis(p[i],p[j]));
                }
        printf("%.2f\n",SPFA(0,n));
    }
    return 0;
}
