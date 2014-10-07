#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MaxN 100005
#define MaxE 400005

int degree[MaxN],ans;  //degree[x]表示x到x父节点这条边被覆盖的次数（度数） 

struct TEdge
{
    int v,next;
}edge[MaxE];
int thead[MaxN],qhead[MaxN],index;

int father[MaxN],vis[MaxN]; //各点的父节点，访问标记
int root,n,m;               //根节点，点数，新加边数 

void InitEdge()
{
    index=0;
    memset(thead,-1,sizeof(thead));
    memset(qhead,-1,sizeof(qhead));
}

void AddTEdge(int u,int v)  //加原图边 
{
    edge[index].v=v;
    edge[index].next=thead[u];
    thead[u]=index++;
}

void AddQEdge(int u,int v)  //加查询边 
{
    edge[index].v=v;
    edge[index].next=qhead[u];
    qhead[u]=index++;
}

int GetFather(int x)
{
    if (father[x]==x) return x;
    father[x]=GetFather(father[x]);
    return father[x];
}

void Union(int x,int y)
{
    int fx,fy;
    fx=GetFather(x);
    fy=GetFather(y);
    if (fx==fy) return; else father[y]=fx;
}

void DFS(int u)
{
    int i,v;
    father[u]=u;  //点的父节点初始化为自己 
    vis[u]=1;     //标记已访问 
    for (i=qhead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (vis[v]) degree[GetFather(v)]-=2;  //对每一条新加边（查询边），其LCA的度减2 
    }
    for (i=thead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (!vis[v])
        {
            DFS(v);
            Union(u,v);
            degree[u]+=degree[v];      //父边被环覆盖的次数要加上子边被环覆盖的次数 
            if (degree[v]==1) ans++;   //只被一个新加边行程的圈覆盖过一次，答案+1 
            if (degree[v]==0) ans+=m;  //没有被圈覆盖，是桥，答案+m 
        }
    }
}

void get(int &a)  //读外挂，节省三分之二的时间 
{  
    char c;  
    while ((c=getchar())<'0'||c>'9');  
    for (a=0;c>='0'&&c<='9';c=getchar()) a=a*10+c-'0';  
}  

int main()
{
    int i,u,v;
    freopen("poj3417.txt","r",stdin);
    freopen("poj3417ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        memset(degree,0,sizeof(degree));
        memset(vis,0,sizeof(vis));
        for (i=1;i<n;i++)
        {
            //scanf("%d%d",&u,&v);
            get(u);
            get(v);
            AddTEdge(u,v);
            AddTEdge(v,u);
        }
        for (i=1;i<=m;i++)
        {
            //scanf("%d%d",&u,&v);
            get(u);
            get(v);
            if (u!=v)
            {
                AddQEdge(u,v);
                AddQEdge(v,u);
                degree[u]++;
                degree[v]++;
            }
        }
        ans=0;
        DFS(1);
        printf("%d\n",ans);
    }
}
