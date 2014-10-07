#include<stdio.h>
#define MaxN 100005
long long n,m,prime[MaxN],cnt,change,a[MaxN];

void GetPrime()
{
    long long i,j,x=m;
    cnt=0;
    for (i=2;i*i<=x;i++) if (x%i==0)
    {
        prime[++cnt]=i;
        while (x%i==0) x/=i;
    }
    if (x>1) prime[++cnt]=x;
}

long long llpow(long long a,long long b)
{
    long long res=1;
    while (b--) res*=a;
    return res;
}

void GetChange(int pos,int now,int top)
{
    long long x=m;
    int i;
    if (now==top)
    {
        for (i=1;i<top;i++) x/=a[i];
        change+=llpow(x,n);
    }
    for (i=pos;i<=cnt;i++)
    { 
        a[now]=prime[i];
        GetChange(i+1,now+1,top);
    }
}

int main()
{
    long long ans;
    int i; 
    freopen("poj1091.txt","r",stdin);
    freopen("poj1091ans.txt","w",stdout);
    while (scanf("%lld%lld",&n,&m)!=EOF)
    {
        GetPrime();
        ans=llpow(m,n);
        for (i=1;i<=cnt;i++) 
        {
            change=0;
            GetChange(1,1,i+1);
            if (i%2==0) ans+=change;
            else ans-=change;
        }
        printf("%lld\n",ans);
    }
}
