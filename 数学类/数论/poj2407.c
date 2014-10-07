#include<stdio.h>

int euler(int x)
{
    int i,res=x;
    for (i=2;i*i<=x;i++) if (x%i==0)
    {
        res=res/i*(i-1);
        while (x%i==0) x/=i; //保证i一定是素数
    }
    if (x>1) res=res/x*(x-1);
    return res;
}

int main()
{
    int n;
    freopen("poj2407.txt","r",stdin);
    freopen("poj2407ans.txt","w",stdout); 
    while(scanf("%d",&n) && n) printf("%d\n",euler(n));
    return 0;
}
