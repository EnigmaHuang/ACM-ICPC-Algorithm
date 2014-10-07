#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

#define INF 0x3f3f3f3f
#define MaxN 21 


int n,k,ROOT,mst;            //节点总数，度数限制为k，限制节点编号，最终结果 
int g[MaxN][MaxN];           //原始图
int father[MaxN];            //节点n的父节点
int connect[MaxN][MaxN];     //判断边(i,j)是否在生成树中
int maxlen[MaxN];            //从ROOT到节点v的路径上与ROOT无关的最大权边的点
int visit[MaxN],mark[MaxN];  //全局和Prim、DFS用的局部访问标记 

map<string,int> mp;          //名称->编号映射

void DFS(int now)            //用DFS把无根树变成有根树
{
    int i;
    for (i=0;i<n;i++)
    {
        if (connect[i][now] && mark[i])
        {
            father[i]=now;
            mark[i]=0;
            DFS(i);
        }
    }
}

int Prim(int source)//PRIM算法＋生成1度MST
{
    int minlen,key,sum=0,i,subroot;
    int dis[MaxN],pre[MaxN];  //pre[x]表示x点的dis值由哪一点指向 

    memset(pre,0,sizeof(pre));
    memset(mark,0,sizeof(mark));
    mark[source]=1;
    visit[source]=1;
    
    for (i=0;i<n;i++)
    {
        dis[i]=g[source][i];
        pre[i]=source;
    }
    
    while (1)
    {
        minlen=INF;
        for (i=0;i<n;i++)
        {
            if (!visit[i] && !mark[i] && dis[i]<minlen)
            {
                minlen=dis[i];
                key=i;
            }
        }
        if (minlen>=INF) break;
        mark[key]=1;
        visit[key]=1;
        connect[pre[key]][key]=connect[key][pre[key]]=1;
        sum+=minlen;
        for (i=0;i<n;i++)
        {
            if (!visit[i] && !mark[i] && dis[i]>g[key][i])
            {
                dis[i]=g[key][i];
                pre[i]=key;
            }
        }
    }
    
    minlen=INF;
    subroot=-1;      //找到与v0相关联的点的最小边，加入1条边，生成1度MST
    for (i=0;i<n;i++)
    {
        if (mark[i] && g[ROOT][i]<minlen)
        {
            minlen=g[ROOT][i];
            subroot=i;
        }
    }
    mark[subroot]=0;
    DFS(subroot);        //生成有根树
    father[subroot]=ROOT;
    return sum+minlen;
}

int findMaxLen(int x)//记忆化搜索ROOT到x的最大权值的边
{
    int tmp;
    if (father[x]==ROOT) return -1;      //如果节点的父节点是ROOT，不再查找
    if (maxlen[x]!=-1) return maxlen[x]; //如果访问过此节点，返回正确的值
    tmp=findMaxLen(father[x]);
    //取ROOT到上一点的最长边与本点到上一点的边中较长的一条 
    if (tmp!=-1 && g[tmp][father[tmp]]>g[father[x]][x]) maxlen[x]=tmp;
    else maxlen[x]=x; 
    
    return maxlen[x];
}


void solve()
{
    memset(visit,0,sizeof(visit));
    memset(connect,0,sizeof(connect));
    memset(father,-1,sizeof(father));
    visit[ROOT]=1;
    int m=0,i,j,x,fatherx;
    int change;//回路上权值最大的边，用于交换
    mst=0;
    //先求m度限制最小生成树
    for (i=0;i<n;i++)
    {
        if (!visit[i])
        {
            m++;
            mst+=Prim(i);
        }
    }
    //然后做k-m次的替换边操作 
    for (i=1;i<=k-m;i++)
    {
        memset(maxlen,-1,sizeof(maxlen));
        for (j=0;j<n;j++)
        {
            if(maxlen[j]==-1 && father[j]!=ROOT) findMaxLen(j);
        }

        int minadd=INF; // 交换边的最小差值
        //枚举每一条和ROOT相连的边，作为新加入的边
        for (j=0;j<n;j++) if (g[ROOT][j]!=INF && father[j]!=ROOT) 
        {
            x=maxlen[j];
            //取原来ROOT到这个点的路径上的最长的边 
            fatherx=father[x];
            //两者比较取差值
            if (g[ROOT][j]-g[x][fatherx]<minadd)
            {
                minadd=g[ROOT][j]-g[x][fatherx];
                change=j;
            }
        }
        if (minadd>=0) break; //ROOT已经连了所有的边，度数仍小于K，直接退出 
        
        mst+=minadd;        //mst的值加上差值
        //在图中去掉被替换的边 
        x=maxlen[change];
        fatherx=father[x];
        g[x][fatherx]=g[fatherx][x]=INF;
        //修改生成树的信息，将点x直接指向源点ROOT 
        father[x]=fatherx=ROOT;         
        g[x][ROOT]=g[ROOT][x]=g[change][ROOT];
        g[ROOT][change]=g[change][ROOT]=INF;
    }
}

int main()
{
    int m,i,u,v,w;
    freopen("poj1639.txt","r",stdin);
    freopen("poj1639ans.txt","w",stdout);
    memset(g,INF,sizeof(g));
    string str;
    n=1;
    ROOT=0;         //公园是限制点，编号为0 
    mp.clear();
    mp["Park"]=ROOT;
    
    
    scanf("%d",&m);    
    for(i=0;i<m;i++)
    {
        cin >> str;
        if (mp.find(str)==mp.end()) mp[str]=n++;
        u=mp[str];
        
        cin >> str;
        if (mp.find(str)==mp.end()) mp[str]=n++;
        v=mp[str];
        
        scanf("%d",&w);
        if (w<g[u][v]) g[u][v]=g[v][u]=w;
    }
    scanf("%d",&k);
    solve();
    
    printf("Total miles driven: %d",mst);
    return 0;
}
