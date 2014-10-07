#include<stdio.h>

long long C(long long total,long long select)
{
    long long ans,cnt;
    if (total-select<select) select=total-select;
    ans=1;
    cnt=select;
    while (cnt--)
    {
        ans*=total;
        total--;
        while (ans%select==0 && select>1)
        {
       	    ans/=select;
       	    select--;
        }
    }
    return ans;
}

int main()
{
    long long a,b,res;
    freopen("poj1942.txt","r",stdin);
    freopen("poj1942ans.txt","w",stdout);
    while (scanf("%lld %lld",&a,&b)!=EOF)
    {
        if (a==0 && b==0) break;
        printf("%lld\n",C(a+b,a));
    }
    return 0;
}
