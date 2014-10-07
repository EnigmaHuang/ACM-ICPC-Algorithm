#include <cstdlib>  
#include <cstdio>  
#include <cstring> 

#define min(a,b) (a<b)?a:b;
 
using namespace std;  

const int MaxN = 501;  
const int INF  = 0x3F3F3F3F;  

int n,m;
int v[MaxN];          //缩点后的点集 
int map[MaxN][MaxN];  //边权邻接矩阵 
int dis[MaxN];        //缩点后某一点到当前S集的距离 
bool vis[MaxN];       //访问标记 

int Stoer_Wagner(int n)   
{  
    int i,j,res=INF,maxp,prev;
    for (i=0;i<n;i++) v[i]=i;  
    while (n>1)   
    {  
        maxp=1;
        prev=0;  
        for (i=1;i<n;i++) //初始化到S集的割大小,并找出最大距离的顶点  
        {
            dis[v[i]]=map[v[0]][v[i]];  
            if (dis[v[i]]>dis[v[maxp]]) maxp=i;  
        }  
        memset(vis,0,sizeof(vis));  
        vis[v[0]]=1;  
        for (i=1;i<n;i++)   
        {  
            if (i==n-1) //只剩最后一个没加入集合的点，更新最小割  
            {   
                res=min(res,dis[v[maxp]]);  
                for (j=0;j<n;j++) //合并最后一个点以及推出它的集合中的点  
                {   
                    map[v[prev]][v[j]]+=map[v[j]][v[maxp]];  
                    map[v[j]][v[prev]]=map[v[prev]][v[j]];  
                }  
                n--;
                v[maxp]=v[n]; //缩点  
            }  
            vis[v[maxp]]=1;  
            prev=maxp;  
            maxp=-1;  
            for (j=1;j<n;j++) if (!vis[v[j]])   //对于所有还没被搜索过的点 
            {   
                dis[v[j]]+=map[v[prev]][v[j]];  //更新距离值 
                if (maxp==-1 || dis[v[maxp]]<dis[v[j]]) maxp=j;  //更新最大值点 
            }  
        } 
    }
    return res;  
}  

int main()
{   
    while (scanf("%d%d", &n, &m) != EOF)
    {  
        memset(map,0,sizeof (map));  
        int u,v,w;  
        while (m--)
        {  
            scanf("%d%d%d",&u,&v,&w);  
            map[u][v]+=w;  
            map[v][u]+=w;  
        }  
        printf("%d\n",Stoer_Wagner(n));  
    }  
    return 0;  
} 
