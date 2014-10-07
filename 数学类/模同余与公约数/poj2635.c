#include<stdio.h>
#include<string.h>

#define MaxN 1000005
#define MaxP 100000

int p[MaxN],prime[MaxP],cnt,num[20];

void GetPrimeList()
{
    int i,j;
    memset(p,1,sizeof(p));
    for (i=2;i*i<MaxN;i++) if (p[i])
        for (j=2;j*i<MaxN;j++) p[j*i]=0;
    i=2;
    for (j=0;i<MaxN;i++) if (p[i]) prime[j++]=i;
}

int MOD(int mod)
{
    long long ans=0;
    int i;
    for (i=cnt;i>=0;i--) ans=(ans*1000000000+num[i])%mod;
    return (int)ans;
}

int main()
{
    int i,k,l,flag;
    char K[105];
    freopen("poj2635.txt","r",stdin);
    freopen("poj2635ans.txt","w",stdout);
    GetPrimeList();
    while (scanf("%s%d",K,&l) && l)
    {
        memset(num,0,sizeof(num));
        cnt=0;k=1;
        for (i=strlen(K)-1;i>=0;i--)
        {
       	    if (k==1000000000)
       	    {
   	        k=1;
   	        cnt++;
       	    }
       	    num[cnt]+=(K[i]-'0')*k;
       	    k*=10;
        }
        flag=0;
        for (i=0;prime[i]<l;i++) 
	    if (MOD(prime[i])==0)
            {
       	        flag=1;
       	        break;
            }
        if (flag) printf("BAD %d\n",prime[i]);
        else printf("GOOD\n");
    }
    return 0;
}
