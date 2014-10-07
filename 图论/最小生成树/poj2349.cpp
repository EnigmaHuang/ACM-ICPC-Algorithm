#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;

#define MaxN 510
#define MaxE 510*510

int anse[MaxN],pos;

/*---------------Kruskal Template Start---------------*/

struct TEdge
{
    int u,v,w;
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
    //edge[edgenum].used=0;
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

int Kruskal(int nodenum)
{
    int cnt=0,i,res=0,f1,f2; 
    //qsort(edge,edgenum,sizeof(TEdge),cmp);
    QSort(0,edgenum-1); 
    for (i=1;i<=nodenum;i++) father[i]=i;  //初始化并查集 
    for (i=0;i<edgenum;i++)
    {
        f1=GetFather(edge[i].u);
        f2=GetFather(edge[i].v);
        if (f1!=f2)
        {
            father[f1]=f2;
            res+=edge[i].w;
            anse[++pos]=edge[i].w;
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    return res;
}

/*---------------Kruskal Template Start---------------*/

struct TPosi
{
    int x,y;
}city[MaxN];

int dist(TPosi a,TPosi b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int main()
{
    int testcase,s,n,i,j;
    freopen("poj2349.txt","r",stdin);
    freopen("poj2349ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d%d",&s,&n);
        InitEdge();
        for (i=1;i<=n;i++) scanf("%d%d",&city[i].x,&city[i].y);
        for (i=1;i<=n;i++)
            for (j=i+1;j<=n;j++) AddEdge(i,j,dist(city[i],city[j]));
        pos=0;
        Kruskal(n);
        pos=pos-(s-1);
        printf("%.2f\n",sqrt(anse[pos])); //血泪警告，GCC/G++要用%.2f而不是%.2lf 
    }
    return 0;
}
