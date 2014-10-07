#include <stdio.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 100000

/*不知道为什么用GCC 1200+ms，用C 500+ms*/ 

int max[MaxN][20];
int first[MaxN];

void STDP(int nodenum)
{
    int i,j;
    for (i=1;i<=nodenum;i++) max[i][0]=first[i];  
    for (j=1;(1<<j)<=nodenum;j++)
        for (i=1;i+(1<<j)-1<=nodenum;i++)
            max[i][j]=Max(max[i][j-1],max[i+(1<<(j-1))][j-1]);
}

int MaxRMQ(int l,int r)
{
    int k=0;
    if (l>r) return 0;
    while ( (1<<(k+1)) <= r-l+1 ) k++;
    return Max(max[l][k],max[r+1-(1<<k)][k]);
}

int num[MaxN];

int main()
{
    int i,n,q,a,b,t,rmq,ans;
    freopen("poj3368.txt","r",stdin);
    freopen("poj3368ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        scanf("%d",&q);
        for (i=1;i<=n;i++)
	{
	    scanf("%d",&num[i]);
	    if (i==1)
	    {
                first[i]=1;
                continue;
	    }
	    if (num[i]==num[i-1]) first[i]=first[i-1]+1;
            else first[i]=1;
	} 
	STDP(n);
	for (i=1;i<=q;i++)
	{
	    scanf("%d%d",&a,&b);
	    t=a;                
	    while (t<=b && num[t]==num[t-1]) t++; 
	    rmq=MaxRMQ(t,b);    //要把前面相同的截掉  
	    ans=Max(rmq,t-a);   //因为此时它们的max值并没有对应完整的序列
	    printf("%d\n",ans);
	}
    }
    return 0;
}
