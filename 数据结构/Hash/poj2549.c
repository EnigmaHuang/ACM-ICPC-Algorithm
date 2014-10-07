#include<stdio.h>
#include<string.h>

#define UNUSED 0x3f3f3f3f3f3f3f3f
#define MaxN   1000005
#define prime  99991

struct TNode
{
    int i,j,next;
}rec[MaxN];

int hash[prime],index;
long long s[1001];
int n;

void QSort(int l,int r)
{
    int i=l,j=r;
    long long mid=s[(l+r)/2],swap;
    while (i<=j)
    {
        while (s[i]>mid) i++;
        while (s[j]<mid) j--;
        if (i<=j)
        {
            swap=s[i];
            s[i]=s[j];
            s[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

long long ABS(long long x)
{
    return x>0LL?x:-x;
}

int main()
{
    int i,j,flag,k,ii,jj;
    long long sum,ans;
    freopen("poj2549.txt","r",stdin);
    freopen("poj2549ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF && n)
    {
        memset(hash,-1,sizeof(hash));
        for (i=0;i<n;i++) scanf("%lld",&s[i]);
        QSort(0,n-1);
        index=0;
        for (i=0;i<n;i++)
            for (j=i+1;j<n;j++)
            {
                rec[index].i=i;
                rec[index].j=j;
                sum=ABS(s[i]+s[j])%prime;
                rec[index].next=hash[sum];
                hash[sum]=index;
                index++;
            }
        flag=0;
        ans=0LL;
        for (i=0;i<n-1 && !flag;i++)
            for (j=i+1;j<n && !flag;j++)
            {
                sum=ABS(s[i]-s[j])%prime;
                for (k=hash[sum];k!=-1;k=rec[k].next)
                {
                    ii=rec[k].i;
                    jj=rec[k].j;
                    if (s[ii]+s[jj]==s[i]-s[j] && ii!=i && ii!=j && jj!=i && jj!=j)
                    {
                        flag=1;
                        ans=s[i];
                        break;
                    }
                }
            }
        if (flag) printf("%lld\n",ans);
        else printf("no solution\n");
    }
    return 0;
}
