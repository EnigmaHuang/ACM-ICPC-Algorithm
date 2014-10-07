#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define MaxN 52
#define MaxM 2550
#define INF 0x3f3f3f3f

/*---------------KM Template Start---------------*/

int w[MaxN][MaxM];
int lx[MaxN],ly[MaxM];
int link[MaxM];
int visx[MaxN],visy[MaxM];
int slack[MaxM];
int numx,numy;

int DFS(int x)
{
    int y,t; 
    visx[x]=1;
    for(y=1;y<=numy;y++)
    {
        if (visy[y]) continue;
        t=lx[x]+ly[y]-w[x][y];
        if (t==0)
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

int KM()
{
    int i,j,x,d,ans;
    for (i=1;i<=numx;i++)
    {
        lx[i]=-INF;
        for (j=1;j<=numy;j++) if (w[i][j]>lx[i]) lx[i]=w[i][j];
    }
    for (x=1;x<=numx;x++)
    {
        for(i=1;i<=numy;i++) slack[i]=INF;
        while (1)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(DFS(x)) break;
            d=INF;
            for (i=1;i<=numy;i++) if (!visy[i] && d>slack[i]) d=slack[i];
            for (i=1;i<=numx;i++) if (visx[i]) lx[i]-=d;
            for (i=1;i<=numy;i++) if (visy[i]) ly[i]+=d;
            else slack[i]-=d;
        }
    }
    ans=0;
    for(i=1;i<=numy;i++) if (link[i]>-1) ans+=w[link[i]][i];
    return ans;
}

void InitKM(int nx,int ny)
{
    numx=nx;
    numy=ny;
    memset(link,-1,sizeof(link));
    memset(ly,0,sizeof(ly));    
} 

/*---------------KM Template Over---------------*/

int n,m;

void ReadData()
{
    scanf("%d%d",&n,&m);
    InitKM(n,n*m);
    int cost,i,j,k,cnt;
    for (i=1;i<=n;i++)
    {
        cnt=1;
        for (j=1;j<=m;j++)
        {
            scanf("%d",&cost);
            for (k=1;k<=n;k++) w[i][cnt++]=-cost*k;
        }
    }
}

int main()
{
    int t;
    double ans; 
    scanf("%d",&t);
    while(t--)
    {
        ReadData();
        ans=(-1.0)*KM()/n;
        printf("%.6f\n",ans);
    }
    return 0;
}
