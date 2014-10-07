#include<stdio.h>
#define MOD 21252 

int main()
{
    int p,e,i,d,t=0,ans;
    freopen("poj1006.txt","r",stdin);
    freopen("poj1006ans.txt","w",stdout);
    while (scanf("%d%d%d%d",&p,&e,&i,&d)!=EOF && p!=-1)
    {
        ans=(5544*p%MOD+14421*e%MOD+1288*i%MOD-d+MOD)%MOD;
	if (ans==0) ans=MOD;
	printf("Case %d: the next triple peak occurs in %d days.\n",++t,ans);  
    }
    return 0;
}
