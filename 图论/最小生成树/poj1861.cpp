#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define MaxN 1005 
#define MaxE 15005 

int ans; 

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
    qsort(edge,edgenum,sizeof(TEdge),cmp); //对边按权从小到大排序 
    for (i=1;i<=nodenum;i++) father[i]=i;  //初始化并查集 
    for (i=0;i<edgenum;i++)
    {
        f1=GetFather(edge[i].u);
        f2=GetFather(edge[i].v);
        if (f1!=f2)
        {
            father[f1]=f2;
            res+=edge[i].w;
            ans=edge[i].w;
            edge[i].used=1;
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    return res;
}

/*---------------Kruskal Template Start---------------*/

int main()
{
    int n,m,i,u,v,w;
    freopen("poj1861.txt","r",stdin);
    freopen("poj1861ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        Kruskal(n);
        printf("%d\n%d\n",ans,n-1);
        for (i=0;i<m;i++) if (edge[i].used) printf("%d %d\n",edge[i].u,edge[i].v);
    }
    return 0;
}
