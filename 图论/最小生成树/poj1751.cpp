#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define MaxN 755
#define MaxE 755*755

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
    return (*(struct TEdge *)a).w - (*(struct TEdge *)b).w ;
}

int GetFather(int x)
{
    if (x!=father[x]) father[x]=GetFather(father[x]); //路径合并 
    return father[x];
}

int Kruskal(int nodenum)
{
    int cnt=0,res=0,i,f1,f2;
    for (i=0;i<edgenum;i++)
    {
        f1=GetFather(edge[i].u);
        f2=GetFather(edge[i].v);
        if (f1!=f2)
        {
            father[f1]=f2;
            //res+=edge[i].w;
            printf("%d %d\n",edge[i].u,edge[i].v);
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    return res;
}

/*---------------Kruskal Template Start---------------*/

void QSort(int l,int r)
{
    int i=l,j=r,mid;
    TEdge swap;
    mid=edge[(l+r)/2].w;
    while (i<=j)
    {
        while (edge[i].w<mid) i++;
        while (edge[j].w>mid) j--;
        if (i<=j)
        {
            swap=edge[i];
            edge[i]=edge[j];
            edge[j]=swap;
            i++;j--;
        }
    }
    if (l<j) QSort(l,j);
    if (i<r) QSort(i,r);
}

struct TPosi
{
    int x,y;
}city[MaxN];

int dist(TPosi a,TPosi b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void RemoveEdge(int u,int v)
{
    int fa,fb;
    fa=GetFather(u);
    fb=GetFather(v);
    if (fa!=fb) father[fa]=fb;
}

int main()
{
    int i,n,m,j,u,v;
    freopen("poj1751.txt","r",stdin);
    freopen("poj1751ans.txt","w",stdout);
    scanf("%d",&n);
    InitEdge();
    for (i=1;i<=n;i++) scanf("%d%d",&city[i].x,&city[i].y);
    for (i=1;i<=n;i++) father[i]=i;  //初始化并查集 
    scanf("%d",&m);
    for (i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        RemoveEdge(u,v);
    }
    for (i=1;i<=n;i++)
        for (j=i+1;j<=n;j++) 
            if (GetFather(i)!=GetFather(j)) AddEdge(i,j,dist(city[i],city[j]));
    //qsort(edge,edgenum,sizeof(TEdge),cmp); //对边按权从小到大排序 
    QSort(0,edgenum-1);
    Kruskal(n);
    return 0;
}
