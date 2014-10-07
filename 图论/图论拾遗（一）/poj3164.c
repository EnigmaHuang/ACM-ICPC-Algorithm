#include<stdio.h>
#include<math.h>
#include<string.h>

#define min(a,b) (a)<(b)?(a):(b)
#define INF  1000000000
#define MaxN 110

double map[MaxN][MaxN];
int visit[MaxN];
int circle[MaxN]; //circle[x]=1表示x点被删掉了
int pre[MaxN];    //pre[x]表示x点的最小入边
int n,m,ROOT;

struct TPoint
{
    double x,y;
}p[MaxN];

double dist(int i,int j)
{
    return sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
}

void dfs(int u)
{
    int i;
    if (visit[u]) return;
    visit[u]=1;
    for (i=1;i<=n;i++) if (map[u][i]<INF) dfs(i);
}

int connect()//深搜，判断是否存在最小树形图
{
    int i;
    dfs(ROOT);
    for (i=1;i<=n;i++) if (!visit[i]) return 0;
    return 1;
}

double solve()
{
    double ans=0;
    int i,j,k;
    memset(circle,0,sizeof(circle));
    while (1)
    {
        for (i=1;i<=n;i++)      //求出每个点的最小入边
        {
            if (circle[i] || i==ROOT) continue;
            map[i][i]=INF;
            pre[i]=i;
            for(j=1;j<=n;j++)
            {
                if (circle[j]) continue;
                if (map[j][i]<map[pre[i]][i]) pre[i]=j;
            }
        }
        for (i=1;i<=n;i++)      //遍历找环
        {
            if (circle[i] || i==ROOT) continue;
            j=i;
            memset(visit,0,sizeof(visit));
            while (!visit[j] && j!=1)
            {
                visit[j]=1;
                j=pre[j];
            }
            if (j==ROOT) continue; //j==ROOT说明i不在环上
            i=j;                   //找到了环
            ans+=map[pre[i]][i];
            for (j=pre[i];j!=i;j=pre[j])
            {
                ans+=map[pre[j]][j];
                circle[j]=1;    //用环上一点i代表此环，其他点删去，即circle[j]=1
            }
            for(j=1;j<=n;j++)
            {
                if (circle[j]) continue;
                if (map[j][i]<INF) map[j][i]-=map[pre[i]][i]; //更新j的入边
            }
            for (j=pre[i];j!=i;j=pre[j])//环上所有点的最优边为人工顶点的边
            {
                for (k=1;k<=n;k++)      //重新构边，更新边权
                {
                    if (circle[k]) continue;
                    if (map[j][k]<INF) map[i][k]=min(map[i][k],map[j][k]);
                    if (map[k][j]<INF) map[k][i]=min(map[k][i],map[k][j]-map[pre[j]][j]);
                }
            }
            break;  //找一个环以后因为重新构了边所以要重新找环
        }
        if (i>n)    //没有环了，直接计算答案并返回
        {
            for (j=1;j<=n;j++)
            {
                if (circle[j] || j==ROOT) continue;
                ans+=map[pre[j]][j];
            }
            break;
        }
    }
    return ans;
}

int main()
{
    int i,j,a,b;
    freopen("poj3164.txt","r",stdin);
    freopen("poj3164ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++) map[i][j]=INF;
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            map[a][b]=dist(a,b);
        }
        ROOT=1;
        memset(visit,0,sizeof(visit));
        if (!connect()) printf("poor snoopy\n");
        else printf("%.2f\n",solve());  //GCC/C++这里不能用%.2lf
    }
    return 0;
}
