#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

#define MaxN 102
#define INF 9999999999.0
#define eps 1e-5

/*---------------KM Template Start---------------*/

double w[MaxN][MaxN];
double lx[MaxN],ly[MaxN];
int link[MaxN];
bool visx[MaxN],visy[MaxN];
double slack[MaxN];
int numx,numy;

int DFS(int x)
{
    int y;
    double t;
    visx[x]=1;
    for(y=1;y<=numy;y++)
    {
        if(visy[y]) continue;
        t=lx[x]+ly[y]-w[x][y];
        if(abs(t)<eps)
        {
            visy[y]=1;
            if(link[y]==-1 || DFS(link[y]))
            {
                link[y]=x;
                return 1;
            }
        }
        else if(slack[y]>t) slack[y]=t;
    }
    return 0;
}

void KM()
{
    int i,j,x;
    double d;
    memset(link,-1,sizeof(link));
    memset(ly,0,sizeof(ly));
    for(i=1;i<=numx;i++)
    {
        lx[i]=-INF;
        for(j=1;j<=numy;j++) if(w[i][j]>lx[i])lx[i]=w[i][j];
    }
    for(x=1;x<=numx;x++)
    {
        for(i=1;i<=numy;i++) slack[i]=INF;
        while (1)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(DFS(x)) break;
            d=INF;
            for(i=1;i<=numy;i++) if(!visy[i] && d>slack[i]) d=slack[i];
            for(i=1;i<=numx;i++) if(visx[i]) lx[i]-=d;
            for(i=1;i<=numy;i++) if(visy[i]) ly[i]+=d;
            else slack[i]-=d;
        }
    }
}

void InitKM(int nx,int ny)
{
    numx=nx;
    numy=ny;
    memset(link,-1,sizeof(link));
    memset(ly,0,sizeof(ly));     
    memset(w,0,sizeof(w)); 
}

/*---------------KM Template Over---------------*/

struct TPoint
{
    double x,y;
}ant[MaxN],apple[MaxN];

double dist(TPoint a,TPoint b)
{
    return -sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int main()
{
    int i,j,n;
    freopen("poj3565.txt","r",stdin);
    freopen("poj3565ans.txt","w",stdout);
    while(scanf("%d",&n)!=EOF)
    {
        InitKM(n,n);
        for(i=1;i<=numx;i++) scanf("%lf%lf",&ant[i].x,&ant[i].y);
        for(i=1;i<=numy;i++) scanf("%lf%lf",&apple[i].x,&apple[i].y);
        for(i=1;i<=numy;i++)
            for(j=1;j<=numx;j++) w[i][j]=dist(apple[i],ant[j]);
        KM();
        for(i=1;i<=numy;i++) printf("%d\n",link[i]);
    }
    return 0;
}
