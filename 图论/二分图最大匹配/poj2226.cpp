#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MaxN 1000
#define MaxE 52*52 

/*---------------Hungary Template Start---------------*/

struct TEdge
{
    int u,v,next;
}edge[MaxE];
int head[MaxN],index;
int link[MaxN],vis[MaxN],pointnum;

void AddEdge(int src,int trg)
{
    edge[index].u=src;
    edge[index].v=trg;
    edge[index].next=head[src];
    head[src]=index++;
}

void InitMap(int pn)
{
    pointnum=pn;
    index=0;
    memset(head,-1,sizeof(head));
}

int Find(int u)  
{  
    int i,v;
    for(i=head[u];i!=-1;i=edge[i].next)  
    {
        v=edge[i].v;
        if (!vis[v])
        {
       	    vis[v]=1;
       	    if (link[v]==-1 || Find(link[v])) //Y部图的点还没被匹配，或者已经被匹配但是可以重新匹配
            {
                link[v]=u;
                return 1;
            } 
        }
    }
   return 0;
} 

int Hungary()  
{  
    int i,res; 
    res=0; 
    memset(link,-1,sizeof(link));
    for(i=1;i<=pointnum;i++)
    {  
        memset(vis,0,sizeof(vis));  
        if (Find(i)) res++;  //对每一个点都寻找一次匹配 
    }
    return res;
}

/*---------------Hungary Template Over---------------*/

int mapx[52][52],mapy[52][52];

int main()
{
    int row,col,r,c,cnt,flag,cnt2;
    char chr;
    freopen("poj2226.txt","r",stdin);
    freopen("poj2226ans.txt","w",stdout);
    while (scanf("%d%d\n",&row,&col)!=EOF)
    {
        memset(mapx,0,sizeof(mapx));
        //读入，顺便横向进行进行点编号 
        cnt=0;
        for (r=1;r<=row;r++)
        {
       	    flag=1;
       	    for (c=1;c<=col;c++)
       	    {
                scanf("%c",&chr);
                if (chr=='*')
                {
               	    if (flag) 
                    {
               	        cnt++;
               	        flag=0;
                    }
                    mapx[r][c]=cnt;
                }
                if (chr=='.') flag=1;
            }
       	    scanf("\n");
        }
        cnt2=cnt;
        //纵向进行点编号 
        cnt=0;
        for (c=1;c<=col;c++)
        {
       	    flag=1;
       	    for (r=1;r<=row;r++)
       	    {
   	        if (mapx[r][c]) //这个点被编号了，即为*
                {
               	    if (flag)
               	    {
                        cnt++;
                        flag=0;
               	    }
               	    mapy[r][c]=cnt;
                }
                else flag=1;
       	    }
        }
        if (cnt2>cnt) cnt=cnt2;
        InitMap(cnt);
        for (r=1;r<=row;r++)
            for (c=1;c<=col;c++) if (mapx[r][c])
            {
                AddEdge(mapx[r][c],mapy[r][c]);
            }
        printf("%d\n",Hungary());
    }
    return 0;
} 
