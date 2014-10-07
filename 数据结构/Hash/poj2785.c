#include<stdio.h>
#include<string.h>

#define UNUSED 0x3f3f3f3f
#define MaxN   4005
#define size   20345677
#define step   1777

int n,a[MaxN],b[MaxN],c[MaxN],d[MaxN],ans;
int hash[size],sum[size];

void Insert(int num)
{
    int pos=num;
    pos=(pos+UNUSED)%size;
    while (hash[pos]!=UNUSED && hash[pos]!=num) pos=(pos+step)%size;
    hash[pos]=num;
    sum[pos]++;
}

int Find(int num)
{
    int pos=num;
    pos=(pos+UNUSED)%size;
    while (hash[pos]!=UNUSED && hash[pos]!=num) pos=(pos+step)%size;
    if (hash[pos]==UNUSED) return 0;
    else return sum[pos];
}

int main()
{
    int i,j;
    freopen("poj2785.txt","r",stdin);
    freopen("poj2785ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
        memset(hash,UNUSED,sizeof(hash));
        for (i=0;i<n;i++)
            for (j=0;j<n;j++)
                Insert(a[i]+b[j]);
        for (i=0;i<n;i++)
            for (j=0;j<n;j++)
                ans+=Find(-(c[i]+d[j]));
        printf("%d\n",ans);
    }
    return 0;
}
