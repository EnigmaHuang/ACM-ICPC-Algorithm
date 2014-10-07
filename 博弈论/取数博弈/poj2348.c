#include<stdio.h>

int cnt;

void Check(long long n,long long m)
{
    cnt++;
    if (n==m || n>=2*m) return;
    Check(m,n-m);
}

int main()
{
    long long n,m,swap;
    while (scanf("%lld%lld",&n,&m)!=EOF)
    {
        if (n==0LL && m==0LL) break;
        if (n<m)
        {
            swap=n;
            n=m;
            m=swap;
        }
        cnt=0;
        Check(n,m);
        if (cnt%2!=0) printf("Stan wins\n");
        else printf("Ollie wins\n");
    }
    return 0;
}
