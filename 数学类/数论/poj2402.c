#include<stdio.h>
#include<string.h>

long long pow10(long long w)
{
    long long sum=1;
    while (w--) sum*=10;
    return sum;    
}

int main()
{
    long long n,s,ans,i,cycnum[30],t,j;
    freopen("poj2402.txt","r",stdin);
    freopen("poj2402ans.txt","w",stdout);
    memset(cycnum,0,sizeof(cycnum));
    s=cycnum[1]=cycnum[2]=9;
    for (i=3;i<30;i+=2)
    {   
        s*=10; 
        cycnum[i]=cycnum[i+1]=s;    
    }
    while (scanf("%lld",&n)!=EOF && n)
    {
        for (i=1;n>cycnum[i];i++) n-=cycnum[i];
        s=i;
        if (s%2) s=s/2+1; else s/=2;
        s=pow10(s-1)+n-1;
        printf("%lld",s); //正着输出一次 
        if (i%2==1) s/=10;
        while (s)        //反着输出一次 
	{
	    printf("%d",s%10); 
	    s/=10;
        } 
        printf("\n");     
    } 
    return 0;
}
