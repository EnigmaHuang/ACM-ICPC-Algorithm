#include<stdio.h>
#define MaxN 10005
//其实到1005也能过，但是我还是不太放心 
int prime[MaxN],cnt;

int IsPrime(int x)
{
    int i;
    for (i=2;i*i<=x;i++) if (x%i==0) return 0;
    return 1;
}

void MakePrimeList()
{
    int i=3;
    cnt=1;
    prime[cnt]=2;
    while (cnt<MaxN)
    {
        if (IsPrime(i)) prime[++cnt]=i;
        i++;
    }
}

int SumNum(int x)
{
    int res=0;
    while (x)
    {
        res+=x%10;
        x/=10;
    }
    return res;
}

int SumFactor(int x)
{
    int i,res=0;
    for (i=1;i<=cnt && x>=prime[i];i++)
    {
        while (x%prime[i]==0)
        {
       	    res+=SumNum(prime[i]);
       	    x/=prime[i];
        }
    }
    if (x>1) res+=SumNum(x);
    return res;
}

int main()
{
    int num;
    freopen("poj1142.txt","r",stdin);
    freopen("poj1142ans.txt","w",stdout);
    MakePrimeList();
    while (scanf("%d",&num) && num)
    {
        while (1)
        {
       	    num++;
       	    if (IsPrime(num)) continue;
       	    if (SumNum(num)==SumFactor(num)) break;
        }
        printf("%d\n",num);
    }
    return 0;
}
