#include <stdio.h>
#define MaxN 100005


struct TLeftTree
{
    int l,r,v,dis;  //左子树右子树，权值，距离值
    int fa;         //父节点
}heap[MaxN];

void swap(int &a,int &b)
{
    int c=a;a=b;b=c;
}

int Merge(int a,int b)
{
    if (a==0) return b;
    if (b==0) return a;
    if (heap[a].v<heap[b].v) swap(a,b);
    heap[a].r=Merge(heap[a].r,b);
    heap[heap[a].r].fa=a;
    if (heap[heap[a].l].dis<heap[heap[a].r].dis) swap(heap[a].l,heap[a].r);
    if (heap[a].r==0) heap[a].dis=0;
    else heap[a].dis=heap[heap[a].r].dis+1;
    return a;
}


int Pop(int a)
{
    int l=heap[a].l;
    int r=heap[a].r;
    heap[l].fa=l;
    heap[r].fa=r;
    heap[a].l=heap[a].r=heap[a].dis=0;
    return Merge(l,r);
}


int find(int a)
{
    return heap[a].fa==a?a:find(heap[a].fa);
}


int main()
{
    int i,a,b,finda,findb,n,m,u,v;
    freopen("hdoj1512.txt","r",stdin);
    freopen("hdoj1512ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=1;i<=n;i++)
        {
            scanf("%d",&heap[i].v);
            heap[i].l=heap[i].r=heap[i].dis=0;
            heap[i].fa=i;
        }
        scanf("%d",&m);
        while (m--)
        {
            scanf("%d%d",&a,&b);
            finda=find(a);
            findb=find(b);
            if (finda==findb) printf("-1\n");
            else
            {
                heap[finda].v/=2;  //修改堆顶值
                u=Pop(finda);      //堆顶出堆
                u=Merge(u,finda);  //重新压入并调整位置
                heap[findb].v/=2;
                v=Pop(findb);
                v=Merge(v,findb);
                printf("%d\n",heap[Merge(u,v)].v);  //两棵左偏树合并
            }
        }
    }
    return 0;
}
