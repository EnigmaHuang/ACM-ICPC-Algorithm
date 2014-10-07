#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define MaxN 101
#define MaxE 101*101
#define INF  0x3f3f3f3f

int mine,maxe;

/*---------------Kruskal Template Start---------------*/

struct TEdge
{
    int u,v,w,used;
}edge[MaxE];

int father[MaxN],edgenum;

void InitEdge() 
{
    edgenum=0;
}

void AddEdge(int u,int v,int w)
{
    edge[edgenum].u=u;
    edge[edgenum].v=v;
    edge[edgenum].w=w;
    edge[edgenum].used=0;
    edgenum++;
}

int cmp(const void *a, const void *b) //抄回来的写法…… 
{
    return (*(struct TEdge *)a).w - (*(struct TEdge *)b).w;
}

int GetFather(int x)
{
    if (x!=father[x]) father[x]=GetFather(father[x]); //路径合并 
    return father[x];
}

int Kruskal(int nodenum)
{
    int cnt=0,i,res=0,f1,f2;
    for (i=1;i<=nodenum;i++) father[i]=i;  //初始化并查集 
    for (i=0;i<edgenum;i++)
    {
        if (edge[i].used) continue;
        f1=GetFather(edge[i].u);
        f2=GetFather(edge[i].v);
        if (f1!=f2)
        {
            father[f1]=f2;
            res+=edge[i].w;
            maxe=edge[i].w;
            //edge[i].used=1;
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    if (cnt<nodenum-1) res=-1;
    return res;
}

/*---------------Kruskal Template Start---------------*/

int main()
{
    int n,m,u,v,w,i,j,res,ans;
    freopen("poj3522.txt","r",stdin);
    freopen("poj3522ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m))
    {
        if (n==0 && m==0) break;
        InitEdge();
        while (m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        qsort(edge,edgenum,sizeof(TEdge),cmp); //对边按权从小到大排序 
        ans=INF;
        if (edgenum==0) ans=-1;
        for (i=0;i<edgenum;i++)
        {
            mine=edge[i].w;
            res=Kruskal(n);
            if (res==-1) 
            {
                if (ans==INF) ans=-1;
                break;
            }
            if (maxe-mine<ans) ans=maxe-mine;
            edge[i].used=1;  //屏蔽掉现在最小的那条边 
        }
        printf("%d\n",ans);
    }
}
