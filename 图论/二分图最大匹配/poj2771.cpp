#include <cstdlib>
#include <stdio.h>	
#include <string.h>

#define MaxPoint 505

int n;

int map[MaxPoint][MaxPoint], visited[MaxPoint], marry[MaxPoint];

struct TStudent
{
    int h;
    char sex[5], style[105], fav[105];
}stu[505];

int judge(int x, int y)
{
    if (abs(stu[x].h-stu[y].h)>40)
        return 0;
    else if (stu[x].sex[0]==stu[y].sex[0])
        return 0;
    else if (strcmp(stu[x].style, stu[y].style))
        return 0;
    else if (!strcmp(stu[x].fav,stu[y].fav))
        return 0;
    else return 1;
}

int find(int u) 
{
    for (int i=1;i<=n;i++) 
	{
        if (!map[u][i] || visited[i]) continue;
        visited[i]=1;
        
        if (!marry[i] || find(marry[i])) 
		{
            marry[i]=u;
            return 1;
        }
    }
    return 0;
}

int main()
{
    int testcase,ans,i,j;
    
    scanf("%d",&testcase);
    
    while (testcase--) 
	{    
        memset(map,0,sizeof(map));
        memset(marry,0,sizeof(marry));
        
        scanf("%d", &n);
        for (int i=1;i<=n;i++)
		   scanf("%d %s %s %s",&stu[i].h,stu[i].sex,stu[i].style,stu[i].fav);
		   
        for (i=1;i<=n;i++) 
		{
            for (j=1;j<=n;j++) 
			{
                if (judge(i,j)) map[i][j]=1;
            }
        }   
        for (int i=1;i<=n;i++) 
		{
            memset(visited,0,sizeof(visited));
            if (find(i)) ans++;
        }
        
        printf("%d\n", n-(ans>>1));
    }
    return 0;
}
