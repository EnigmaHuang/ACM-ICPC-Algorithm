#include<stdio.h>

//单变元模线性方程组：已知abn，求x满足ax=b(mod n) 
//x,y为ax+by=GCD(a,b)的一组解，返回值为gcd(a,n) 
long long ExtendGCD(long long a,long long b,long long &x,long long &y)
{
    if (b==0)
    {
        x=1;y=0;
        return a;
    }
    else
    {
        int r=ExtendGCD(b,a%b,y,x);
        y-=x*(a/b);
	return r; 
    }
}

long long ModularLinearEquation(long long a,long long b,long long n)
{
    long long x,y,e,d=ExtendGCD(a,n,x,y);
    if (b%d!=0) return -1;
    e=(x*(b/d)%n)+n;
    e%=(n/d);
    return e;
} 

int main()
{
    freopen("poj2115.txt","r",stdin);
    freopen("poj2115ans.txt","w",stdout);
    long long a,b,c,k,ans;
    while (scanf("%lld %lld %lld %lld",&a,&b,&c,&k)!=EOF)
    {
        if (a==0 && b==0 && c==0 && k==0) break;
        ans=ModularLinearEquation(c,b-a,1LL << k);
        if (ans==-1) printf("FOREVER\n");
        else printf("%lld\n",ans);
    }
    return 0;
} 
