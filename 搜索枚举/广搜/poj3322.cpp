#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;

#define MaxN 505

struct TState
{
    int x,y,steps;
    int state;      //0=竖立，1=横平放，2=竖平放
    TState(int _x=0,int _y=0,int _steps=0,int _state=0)
    :x(_x),y(_y),steps(_steps),state(_state) {}
};

const int dirs[3][4][3]=
{
    {{2,0,2},  {-1,0,2}, {0,-1,1}, {0,2,1}},
    {{0,-2,0}, {0,1,0},  {-1,0,1}, {1,0,1}},
    {{-2,0,0}, {1,0,0},  {0,1,2},  {0,-1,2}}
};

int    vis[MaxN][MaxN][3];
char   map[MaxN][MaxN];
TState src,dst;
int    row,col;

queue<TState> q;

int BFS()
{
    TState now;
    int i,x,y,dir;
    
    memset(vis,0,sizeof(vis));
    while (!q.empty()) q.pop();
    vis[src.x][src.y][src.state]=1;
    q.push(src);
    
    while (!q.empty())
    {
        now=q.front();
        q.pop();
        if (now.x==dst.x && now.y==dst.y && now.state==0) return now.steps;
        for (i=0;i<4;i++)
        {
            x=now.x+dirs[now.state][i][0];
            y=now.y+dirs[now.state][i][1];
            dir=dirs[now.state][i][2];
            if (x>=1 && x<=row && y>=1 && y<=col && !vis[x][y][dir])
            {
                if (dir==0 && map[x][y]!='#' && map[x][y]!='E')
                {
                    vis[x][y][dir]=1;
                    q.push(TState(x,y,now.steps+1,dir));
                }
                else if (dir==1 && map[x][y]!='#' && map[x][y-1]!='#')
                {
                    vis[x][y][dir]=1;
                    q.push(TState(x,y,now.steps+1,dir));
                }
                else if (dir==2 && map[x][y]!='#' && map[x-1][y]!='#')
                {
                    vis[x][y][dir]=1;
                    q.push(TState(x,y,now.steps+1,dir));
                }
            }
        }
    }
    return -1;
}

int main()
{
    int i,j,xcnt,ans;
    char c;
    freopen("poj3322.txt","r",stdin);
    freopen("poj3322ans.txt","w",stdout);
    while (scanf("%d %d\n",&row,&col)!=EOF && row && col)
    {
        xcnt=0;
        for (i=1;i<=row;i++)
        {
            for (j=1;j<=col;j++)
            {
                scanf("%c",&c);
                map[i][j]=c;
                if (c=='O') dst=TState(i,j,0,0);
                else if (c=='X')
                {
                    if (xcnt==0)
                    {
                        src=TState(i,j,0,0);
                        xcnt++;
                    }
                    else if (xcnt==1)
                    {
                        if (j==src.y) src=TState(i,j,0,2);
                        else src=TState(i,j,0,1);
                    }
                }
            }
            scanf("%c",&c);
        }
        ans=BFS();
        if (ans!=-1) printf("%d\n",ans);
        else printf("Impossible\n");
    }
    return 0;
}
