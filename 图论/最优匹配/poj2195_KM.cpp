#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxN 110
#define INF 0x3f3f3f3f

using namespace std;

/*---------------KM Template Start---------------*/

int numx,numy;              //x点集y点集的个数 
int lx[MaxN],ly[MaxN];      //lx,ly为顶标
int link[MaxN],slack[MaxN]; //link表示Y部某一点是由X部哪一点指向的 
int visx[MaxN],visy[MaxN];  //标记搜索增广轨中哪些点被访问 
int w[MaxN][MaxN];          //边权网 

int DFS(int x)
{
    int y,t; 
    visx[x]=1;
    for (y=1;y<=numy;y++)
    {
        if (visy[y]) continue;
        t=lx[x]+ly[y]-w[x][y];
        if (t==0)   
        {
            visy[y]=1;
            if (link[y]==-1 || DFS(link[y]))
            {
                link[y]=x;
                return 1;
            }
        }
        else if (slack[y]>t) slack[y]=t; //不在相等子图中slack取最小的
    }
    return 0;
}

int KM()
{
    int i,j,x,d,res;
    for (i=1;i<=numx;i++)            //lx初始化为与它关联边中最大的
    {
    	lx[i]=-INF;
    	for (j=1;j<=numy;j++) if (w[i][j]>lx[i]) lx[i]=w[i][j];
    }  
    for (x=1;x<=numx;x++)
    {
        memset(slack,INF,sizeof(slack));
        while (1)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if (DFS(x)) break; //找增广轨成功，该点增广完成，进入下一个点的增广   
	    //找增广轨失败，需改变一些点的标号，使得图中可行边的数量增加
            //方法为将所有在增广过程中遍历到的X方点的标号全部减去一个常数d
            //所有在增广轨中的Y方点的标号全部加上一个常数d
            d=INF;
            for (i=1;i<=numy;i++) if (!visy[i]&&d>slack[i]) d=slack[i];
            //修改顶标后，要把所有不在交错树中的Y顶点的slack值都减去d
            for (i=1;i<=numx;i++) if (visx[i]) lx[i]-=d;
            for (i=1;i<=numy;i++) if (visy[i]) ly[i]+=d;
            else slack[i]-=d;
        }
    }
    res=0;
    for (i=1;i<=numy;i++) if (link[i]>-1) res+=w[link[i]][i];
    return res;
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

struct TPos
{
    int x,y;
}house[MaxN],man[MaxN];

int n,m,numh,numm;

void ReadData()
{
    int i,j,dis;
    char c;
    numh=numm=0;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++)
        {
            scanf("%c",&c);
            if ('H'==c)
            {
                numh++;
                house[numh].x=i;
                house[numh].y=j;
            }
            else if ('m'==c)
            {
                numm++;
                man[numm].x=i;
                man[numm].y=j;
            }
        }
        scanf("\n");
    }
    InitKM(numm,numh);
    for (i=1;i<=numm;i++)
    {
        for (j=1;j<=numh;j++)
        {
            dis=abs(man[i].x-house[j].x)+abs(man[i].y-house[j].y);
            w[i][j]=-dis;
        }
    }
}

int main()
{
    freopen("poj2195.txt","r",stdin);
    freopen("poj2195ans.txt","w",stdout);
    while(scanf("%d%d\n",&n,&m)!=EOF)
    {
        if (0==n && 0==m) break;
        ReadData();
        printf("%d\n",-KM());
    }
    return 0;
} 
