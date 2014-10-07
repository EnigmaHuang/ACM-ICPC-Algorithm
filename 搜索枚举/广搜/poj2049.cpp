#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;
#define MaxN 210
#define INF 0x3f3f3f3f

#define Min(a,b) (a)>(b)?(b):(a)
#define Max(a,b) (a)>(b)?(a):(b)

#define EMPTY 0
#define DOOR  1
#define WALL  INF

int UpEdge[MaxN][MaxN];
int RightEdge[MaxN][MaxN];
int dis[MaxN][MaxN];
int dt[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int xmax,ymax;

struct TPos
{
    int x,y;
};

int InMap(int x,int y)
{
    if (x>0 && x<=xmax && y<=ymax && y>0) return 1;
    else return 0;
}

int GetDist(int x,int y,int i)
{
    if (i==0) return RightEdge[x-1][y];
    if (i==1) return RightEdge[x][y];
    if (i==2) return UpEdge[x][y-1];
    if (i==3) return UpEdge[x][y];
}

int BFS(int TargetX,int TargetY)
{
    int i,j,tmp,nx,ny;
    queue<TPos> q;
    TPos now,newpos;

    while (!q.empty()) q.pop();
    
    for (i=1;i<=ymax;i++)
        for (j=1;j<=xmax;j++) dis[i][j]=INF;
        
    now.x=now.y=1;
    dis[1][1]=0;
    q.push(now);

    while (!q.empty())
    {
        now=q.front();
        q.pop();
        for (i=0;i<4;i++)
        {
            nx=now.x+dt[i][0];
            ny=now.y+dt[i][1];
            tmp=GetDist(now.x,now.y,i);
            if (InMap(nx,ny) && dis[nx][ny]>dis[now.x][now.y]+tmp)
            {
                dis[nx][ny]=dis[now.x][now.y]+tmp;
                newpos.x=nx;
                newpos.y=ny;
                q.push(newpos);
            }
        }
    }

    if (dis[TargetX][TargetY]==INF) return -1;
    else return dis[TargetX][TargetY];
}

int main()
{
    int n,m,i,j;
    int x,y,d,t;
    double sx,sy;

    freopen("poj2049.txt","r",stdin);
    freopen("poj2049ans.txt","w",stdout);

    while (scanf("%d%d",&m,&n)!=EOF)
    {
        if(m==-1 && n==-1) break;

        ymax=xmax=-1;
        memset(UpEdge,EMPTY,sizeof(UpEdge));
        memset(RightEdge,EMPTY,sizeof(RightEdge));

        for(i=0;i<m;i++)
        {
            scanf("%d%d%d%d",&x,&y,&d,&t);
            if (d)
            {
                for (j=0;j<t;j++) RightEdge[x][y+j+1]=WALL;
                ymax=Max(y+t+1,ymax);
                xmax=Max(x+1,xmax);
            }
            else
            {
                for (j=0;j<t;j++) UpEdge[x+j+1][y]=WALL;
                ymax=Max(y+1,ymax);
                xmax=Max(x+t+1,xmax);
            }
        }

        for (i=0;i<n;i++)
        {
            scanf("%d%d%d",&x,&y,&d);
            if (d) RightEdge[x][y+1]=DOOR;
            else UpEdge[x+1][y]=DOOR;
        }

        scanf("%lf%lf",&sx,&sy);
        if (!(sx>=1.0 && sx<=199.0 && sy>=1.0 && sy<=199.0)) printf("0\n");
        else printf("%d\n",BFS((int)(sx+1),(int)(sy+1)));
    }
    return 0;
}
