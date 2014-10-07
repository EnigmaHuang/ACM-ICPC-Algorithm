#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define MaxN 27

/*----------Hungary Template Start----------*/

int map[MaxN][MaxN],link[MaxN],vis[MaxN],pointnum;

int Find(int u) 
{  
   int i;
   for(i=1;i<=pointnum;i++)  
   {  
       if( (!vis[i]) && (map[u][i]) )  
       {  
           vis[i]=1;  
           if( (link[i]==-1) || Find(link[i]) )  
           {  
               link[i]=u;  
               return 1;  
           }  
       }  
   }  
   return 0;  
} 

int Hungary(int pn)
{
    int i,res=0;
    pointnum=pn;
    memset(link,-1,sizeof(link));
    for (i=1;i<=pointnum;i++)
    {
        memset(vis,0,sizeof(vis));
        if (Find(i)) res++;
    }
    return res;
}

/*----------Hungary Template Over----------*/

struct TPoint
{
    int x,y;
}num[MaxN];

struct TRect
{
    TPoint LeftUp,RightDown;
}heap[MaxN];

int PointInRect(TPoint APoint,TRect ARect)
{
    if (  ARect.LeftUp.x<=APoint.x && ARect.RightDown.x>=APoint.x
       && ARect.LeftUp.y<=APoint.y && ARect.RightDown.y>=APoint.y)
    return 1; else return 0;
}

int n;

void ReadData()
{
    int i,j;
    for (i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&heap[i].LeftUp.x,
                         &heap[i].RightDown.x,
                         &heap[i].LeftUp.y,
                         &heap[i].RightDown.y);
    }
    for (i=1;i<=n;i++) scanf("%d%d",&num[i].x,&num[i].y);
    memset(map,0,sizeof(map));
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            if (PointInRect(num[i],heap[j])) map[i][j]=1; 
}

void Solve(int testcase)
{
    int flag=0,i,j;
    char chr;
    printf("Heap %d\n",testcase);
    for (j=1;j<=n;j++)
        for (i=1;i<=n;i++)
        {
            if (!map[i][j]) continue;
            map[i][j]=0;
            if (Hungary(n)<n)
            {
                flag++;
                chr=j+'A'-1;
                printf("(%c,%d) ",chr,i);
            }
            map[i][j]=1;
        }
    if (!flag) printf("none\n\n"); else printf("\n\n");
}

int main()
{
    int i,t=0;
    freopen("poj1486.txt","r",stdin);
    freopen("poj1486ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        ReadData();
        Solve(++t);
    }
    return 0;
}
