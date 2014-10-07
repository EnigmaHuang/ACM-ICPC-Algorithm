#include<stdio.h>
#include<string.h>

int n;

/*  打表发现规律…………
int vis[1010][1010] ;
int dt[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int DFS(int x,int y)
{
    int newx,newy,i,res;
    for (i=0;i<4;i++)
    {
        newx=x+dt[i][0] ;
        newy=y+dt[i][1] ;
        if (newx<0 || newx>=n) continue;
        if (newy<0 || newy>=n) continue;
        if (vis[newx][newy]) continue ;
        vis[newx][newy]=1;
        res=DFS(newx,newy);
        vis[newx][newy]=0;
        if (res==0) return 1;
    }
    return 0;
}


int MakeTable()
{
    memset(vis,0,sizeof(vis));
    vis[0][0]=1;
    for (n=1;n<=8;n++) fprintf(stderr,"n=%d win=%d\n",n,DFS(0,0));
}
*/

int main()
{
    while (scanf("%d",&n) && n) if (n&1) printf("ailyanlu\n"); else printf("8600\n");
    return 0;
}
