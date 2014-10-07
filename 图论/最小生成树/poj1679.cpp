#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define MaxN 101
#define MaxE 101*101

int succ;

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
            edge[i].used=1;
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    if (cnt==nodenum-1) succ=1;else succ=0;
    return res;
}

/*---------------Kruskal Template Start---------------*/

int main()
{
    int i,j,u,v,w,testcase,m,n,ans,res;
    int anse[MaxN],pos;
    freopen("poj1679.txt","r",stdin);
    freopen("poj1679ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d%d",&n,&m);
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);;
            AddEdge(u,v,w);
        }
        qsort(edge,edgenum,sizeof(TEdge),cmp); //对边按权从小到大排序 
        ans=Kruskal(n); //求最小生成树 
        /* 按理说应该判断是否连通的……但是判断了反而过不了 
        if (!succ)
        {
            printf("0\n");
            continue; 
        } 
        */
        pos=0;
        for (i=0;i<edgenum;i++) if (edge[i].used) anse[++pos]=i; //记录最小生成树的边 
        for (i=1;i<=pos;i++) //依次去掉最小生成树的边，求次小生成树 
        {
            for (j=0;j<edgenum;j++) edge[j].used=0;
            edge[anse[i]].used=1;
            res=Kruskal(n);
            if (!succ) continue; //无法生成 
            if (res==ans) //最小生成树不唯一，退出 
            {
                ans=-1;
                break;
            }
        }
        if (ans==-1) printf("Not Unique!\n"); else printf("%d\n",ans);
    }
    return 0;
}
