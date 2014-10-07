#include<stdio.h>
#include<string.h>
#define lowbit(x) (x&(-x))
#define MaxN 20002

struct TCow
{
    int x,w;
}cow[MaxN];

int wNum[MaxN]; //wNum[x]：一侧比声调x小的声调的牛的数量
int wDis[MaxN]; //wDis[x]：一侧比声调x小的声调的牛到端点的距离之和

void add(int *tree,int x,int value)
{
    int i;
    for (i=x;i<=MaxN;i+=lowbit(i)) tree[i]+=value;
}

long long sum(int *tree,int x)
{
    long long res=0;
    int i;
    for (i=x;i;i-=lowbit(i)) res+=tree[i];
    return res;
}

void QSort(TCow p[],int l,int r)
{
    int i=l,j=r,mid=p[(l+r)/2].x;
    TCow swap;
    while (i<=j)
    {
        while (p[i].x<mid) i++;
        while (p[j].x>mid) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

int main()
{
    int i,n;
    long long PreNum,PreDis,ans;
    freopen("poj1990.txt","r",stdin);
    freopen("poj1990ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%d%d",&cow[i].w,&cow[i].x);
        QSort(cow,0,n-1);
        ans=0;
        //到左侧的总能量
        memset(wNum,0,sizeof(wNum));
        memset(wDis,0,sizeof(wDis));
        for (i=0;i<n;i++)
        {
            PreNum=sum(wNum,cow[i].w-1);  //左侧比当前声调小的牛的数量之和
            PreDis=sum(wDis,cow[i].w-1);  //左侧比当前声调小的牛的到0的距离之和
            ans+=(PreNum*cow[i].x-PreDis)*cow[i].w;
            add(wNum,cow[i].w,1);
            add(wDis,cow[i].w,cow[i].x);
        }
        //到右侧的总能量
        memset(wNum,0,sizeof(wNum));
        memset(wDis,0,sizeof(wDis));
        for (i=n-1;i>=0;i--)
        {
            //考虑到声调相等没有被上面到左侧的处理，所以这里要算上
            //直接使用cow[i].w，不必-1，把自身也算上
            PreNum=sum(wNum,cow[i].w);  //左侧比当前声调小的牛的数量之和
            PreDis=sum(wDis,cow[i].w);  //左侧比当前声调小的牛的到0的距离之和
            ans+=(PreDis-PreNum*cow[i].x)*cow[i].w;
            add(wNum,cow[i].w,1);
            add(wDis,cow[i].w,cow[i].x);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
