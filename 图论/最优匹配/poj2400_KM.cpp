#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define MaxN 20
#define MaxM 20
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

int n,cnt,total;

void ReadData()
{
    int i,j,r;
    memset(w,0,sizeof(w));
    scanf("%d",&n);
    InitKM(n,n);
    for (i=1;i<=n;i++)
        for (j=0;j<n;j++)
        {
       	    scanf("%d",&r);
       	    w[r][i]-=j;    //取反，另外两个维度是w[员工][老板] 
        }
    for (i=1;i<=n;i++)
        for (j=0;j<n;j++)
        {
       	    scanf("%d",&r);
       	    w[i][r]-=j;    //取反，另外两个维度是w[员工][老板] 
        }    
} 

void DFSOutput(int dep,int sum)
{
    int i,j;
    if (sum>total) return;
    if (dep>n)
    {
        if (sum!=total) return; //理论上不会有这种情况，因为sum>total已经退出了，而total是最优解
        cnt++;
        printf("Best Pairing %d\n",cnt);
        for(i=1;i<= n;i ++) printf("Supervisor %d with Employee %d\n",i,link[i]); 
    }
    else
    {
        for (i=1;i<=n;i++) if (!visy[i])  //注意匹配方向和数组意义！ 
        {
            visy[i]=1;
            link[dep]=i;
            DFSOutput(dep+1,sum-w[dep][i]);
            visy[i]=0;
        }
    }
}

int main()
{
    int cases,testcase;
    double ans;
    freopen("poj2400.txt","r",stdin);
    freopen("poj2400ans.txt","w",stdout);
    scanf("%d",&cases);
    testcase=0;
    while (cases--)
    {
        testcase++;
        ReadData();
        total=-KM();
        ans=(0.5)*total/n;
        printf("Data Set %d, Best average difference: %.6f\n",testcase,ans);
        memset(visy,0,sizeof(visy));
        cnt=0;
        DFSOutput(1,0);
        printf("\n");
    }
}
