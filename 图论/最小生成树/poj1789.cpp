#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define MaxN 2001
#define MaxE 2001*2001

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
            edge[i].used=1;
            cnt++;
            if (cnt==nodenum-1) break;    //已经加入了n-1条边，完成最小生成树 
        }
    }
    return res;
}

/*---------------Kruskal Template Start---------------*/

char s[MaxN][7];
int n;

int StrDist(char* a,char* b)
{
    int i,cnt=0;
    for (i=0;i<7;i++) if (a[i]!=b[i]) cnt++;
    return cnt;
}

int main()
{
    int i,j,w,ans;
    freopen("poj1789.txt","r",stdin);
    freopen("poj1789ans.txt","w",stdout);
    while (scanf("%d\n",&n) && n)
    {
        for (i=1;i<=n;i++) gets(s[i]);
        InitEdge();
        for (i=1;i<=n;i++)
            for (j=i+1;j<=n;j++)
            {
                w=StrDist(s[i],s[j]);
                AddEdge(i,j,w);
            }
        ans=Kruskal(n);
        printf("The highest possible quality is 1/%d.\n",ans);
    }
    return 0;
}
