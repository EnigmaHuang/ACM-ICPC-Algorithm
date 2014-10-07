#include<stdio.h>
#include<string.h>

#define MaxN 10000
#define mod  9901

int prime[MaxN],cnt[MaxN];
int a,b;

long long pow(long long p,long long n)
{
    long long sum=1;
    while (n>0)
    {
        if (n&1) sum=(sum*p)%mod;
        n>>=1;
        p=p*p%mod;
    }
    return sum;
}

long long sum(long long p,long long n)
{
    if (n==0) return 1;
    if (n&1) return ((1+pow(p,n/2+1))*sum(p,n/2))%mod;
    else return ((1+pow(p,n/2+1))*sum(p,n/2-1)+pow(p,n/2))%mod;
}

int main()
{
    int i,k,ans;
    freopen("poj1845.txt","r",stdin);
    freopen("poj1845ans.txt","w",stdout);
    while (scanf("%d%d",&a,&b)!=EOF)
    {
        memset(prime,0,sizeof(prime));
        memset(cnt,0,sizeof(cnt));
        k=0;
        for (i=2;i*i<=a;i++) if (a%i==0)
        {
       	    prime[k]=i;
       	    while (a%i==0)
       	    {
   	        cnt[k]++;
   	        a/=i;
       	    }
       	    k++;
        }
        if (a!=1) //a最后剩下一个素数 
        {
       	    prime[k]=a;
       	    cnt[k++]=1;
        }
        ans=1;
        for (i=0;i<k;i++) ans=ans*(sum(prime[i],cnt[i]*b)%mod)%mod;
        printf("%d\n",ans);
    }
    return 0;
}
