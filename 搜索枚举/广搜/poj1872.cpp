#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>

using namespace std;

struct TPos
{
    int x,y;
    TPos(int _x=0,int _y=0):x(_x),y(_y) {}
};

struct TNode
{
    int x,y,up,fwd;
    vector <TPos> path;
};

int  map[12][12];
int  v[12][12][7][7];
int  right[7][7];       //right[up][fwd]=k表示骰子上为up正面为fwd时右面的数
int  dx[4]={-1,1,0,0};  //要求按上下左右的最小字典序
int  dy[4]={0,0,-1,1};
int  n,m;
int  hasans;
char name[25];

TNode ans;
TPos  dst;

void Print()
{
    int i,size;
    printf("%s\n",name);
    if (!hasans) printf("  No Solution Possible\n");
    else
    {
        printf("  ");
        size=ans.path.size();
        for (i=0;i<size;i++)
        {
            if (i==size-1) printf("(%d,%d)\n",ans.path[i].x,ans.path[i].y);
            else if ((i+1)%9==0) printf("(%d,%d),\n  ",ans.path[i].x,ans.path[i].y);
            else printf("(%d,%d),",ans.path[i].x,ans.path[i].y);
        }
    }
}

void BFS(TNode src)
{
    queue <TNode> Q;
    TNode now,newpos;
    int i,k,x,y,new_fwd,new_up;
    
    Q.push(src);
    hasans=0;
    
    while (!Q.empty())
    {
        now=Q.front();
        Q.pop();
        for (k=0;k<4;k++)
        {
            x=now.x+dx[k];
            y=now.y+dy[k];
            newpos=now;
            new_fwd=now.fwd;
            new_up=now.up;

            if (k==0)  //往上翻
            {
                new_fwd=7-now.up;
                new_up=now.fwd;
            }
            else if (k==1)  //往下翻
            {
                new_up=7-now.fwd;
                new_fwd=now.up;
            } 
            else if (k==2) new_up=right[now.up][now.fwd];  //往左翻
            else new_up=7-right[now.up][now.fwd]; //往右翻

            if (map[x][y]!=0 && (map[x][y]==now.up || map[x][y]==-1)
                && v[x][y][new_up][new_fwd]==0)
            {
                v[x][y][new_up][new_fwd]=1;
                newpos.x=x;
                newpos.y=y;
                newpos.fwd=new_fwd;
                newpos.up=new_up;
                newpos.path.push_back(TPos(x,y));
                Q.push(newpos);

                if (x==dst.x && y==dst.y)
                {
                    hasans=1;
                    ans=newpos;
                    return;
                }
            }
        }
    }
}


int main()
{
    int i,j;
    TNode start;

    freopen("poj1872.txt","r",stdin);
    freopen("poj1872ans.txt","w",stdout);
    
    memset(right,0,sizeof(right));
    //right[up][fwd]=k表示骰子上为up正面为fwd时右面的数
    right[1][2]=3;right[1][3]=5;right[1][4]=2;right[1][5]=4;
    right[2][1]=4;right[2][4]=6;right[2][6]=3;right[2][3]=1;
    right[3][1]=2;right[3][2]=6;right[3][6]=5;right[3][5]=1;
    right[4][1]=5;right[4][5]=6;right[4][6]=2;right[4][2]=1;
    right[5][1]=3;right[5][3]=6;right[5][6]=4;right[5][4]=1;
    right[6][2]=4;right[6][4]=5;right[6][5]=3;right[6][3]=2;

    

    while (scanf("%s",name)!=EOF)
    {
        if (strcmp(name,"END")==0) break;

        memset(map,0,sizeof(map));
        memset(v,0,sizeof(v));
        
        start.path.clear();

        scanf("%d%d%d%d%d%d",&n,&m,&start.x,&start.y,&start.up,&start.fwd);
        for (i=1;i<=n;i++)
            for (j=1;j<=m;j++) scanf("%d",&map[i][j]);

        dst=TPos(start.x,start.y);
        start.path.push_back(dst);

        BFS(start);
        Print();
    }
    return 0;
}

