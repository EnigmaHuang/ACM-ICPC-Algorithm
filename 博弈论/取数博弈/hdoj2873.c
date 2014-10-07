#include<stdio.h>
#include<string.h>

int SG[60][60];
char map[60][60];
int vis[600];

int GetSG(int x,int y)
{
    int i,j;

    memset(vis,-1,sizeof vis);
    
    for(i=0;i<x;i++)
        for(j=0;j<y;j++) vis[SG[i][y]^SG[x][j]]=1;

    for (i=0;i<500;i++) if (vis[i]==-1)
    {
        SG[x][y]=i;
        return i;
    }

}

int main()
{
    int n,m,ans,i,j,a,k;

    freopen("hdoj2873.txt","r",stdin);
    freopen("hdoj2873ans.txt","w",stdout);
    memset(SG,0,sizeof(SG));

    for (i=0;i<=50;i++)  //由题意，地图边缘的SG值可以直接由转移方式得到
    {
        SG[0][i]=i;
        SG[i][0]=i;
    }
    for (i=1;i<=50;i++)
        for (j=1;j<=50;j++) GetSG(i,j);

    while (scanf("%d%d",&n,&m)!=EOF && n)
    {
        ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%s",map[i]);
            for(j=0;j<m;j++) if (map[i][j]=='#') ans^=SG[i][j];
        }
        if (ans) printf("John\n");
        else printf("Jack\n");
    }
}
