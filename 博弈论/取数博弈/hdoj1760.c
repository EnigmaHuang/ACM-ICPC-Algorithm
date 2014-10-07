#include<stdio.h>
#include<string.h>
#define MaxN 55

char map[MaxN][MaxN];
int  m,n;

void Cover(int i,int j,char c)
{
    map[i][j]=map[i][j+1]=map[i+1][j]=map[i+1][j+1]=c;
}

int Check(int i,int j)
{
    if (map[i][j]=='0' && map[i][j+1]=='0'
     && map[i+1][j]=='0' && map[i+1][j+1]=='0')
    return 1;
    else return 0;
}

int DFS()
{
    int i,j;
    for (i=0;i<n;i++)
        for (j=0;j<m;j++)
        {
            if (Check(i,j))
            {
                Cover(i,j,'1');
                if (!DFS())  //下一个状态里有一个必败状态
                {
                    Cover(i,j,'0');
                    return 1;  //这个状态必胜
                }
                Cover(i,j,'0');
            }
        }
    return 0;
}

int main()
{
    int i,j;
    freopen("hdoj1760.txt","r",stdin);
    freopen("hdoj1760ans.txt","w",stdout);
    while (scanf("%d%d\n",&n,&m)!=EOF)
    {
        memset(map,-1,sizeof(map));  //很奇怪，不加这一句会WA
        for (i=0;i<n;i++) scanf("%s",map[i]);  //按道理来说读应该是直接覆盖的
        if (DFS()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
