#include <stdio.h>
#include <string.h>

#define N 201
	
int map[N][N];
int linkto[N];
bool visited[N];
int g,b,m;

bool find(int x)
{
    for(int i=1;i<=b;i++)
    {
        if((!visited[i]) && (map[x][i]))
        {
            visited[i]=1;
            if(linkto[i]==-1 || find(linkto[i]))
            {
                linkto[i]=x;
                return(true);
            }
        }
    }
    return(false);
}
int main()
{
    int cnt=1,boy,girl,ans,i;
    while(1)
    {
        memset(linkto,-1,sizeof(linkto));
        memset(map,1,sizeof(map));
        scanf("%d%d%d",&g,&b,&m);
        if(g==0 && b==0 && m==0) break;
        
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&girl,&boy);
            map[girl][boy]=0;
        }
        
        ans=0;
        for(i=1;i<=g;i++)
        {
            memset(visited,0,sizeof(visited));
            if (find(i)) ans++;
            
        }
        printf("Case %d: %d\n",cnt++,g+b-ans);
    }
}
