#include<stdio.h>
#include<string.h>

#define MaxSize 501

int n,m,d,k;

long long init[MaxSize],opt[MaxSize],tmp[MaxSize];

void Mul1()
{
    int i,j;
    memset(tmp,0,sizeof(tmp));
    for (i=0;i<n;i++)
        for (j=0;j<n;j++) tmp[i]+=opt[j]*init[i>=j?(i-j):(n+i-j)];
    for (i=0;i<n;i++) init[i]=tmp[i]%m;
}

void Mul2()
{
    int i,j;
    memset(tmp,0,sizeof(tmp));
    for (i=0;i<n;i++)
        for (j=0;j<n;j++) tmp[i]+=opt[j]*opt[i>=j?(i-j):(n+i-j)];
    for (i=0;i<n;i++) opt[i]=tmp[i]%m;
}

int main()
{
    int i;
    freopen("poj3150.txt","r",stdin);
    freopen("poj3150ans.txt","w",stdout);
    while (scanf("%d%d%d%d",&n,&m,&d,&k)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%I64d",&init[i]);
        memset(opt,0,sizeof(opt));
        opt[0]=1;
        for (i=1;i<=d;i++) opt[i]=opt[n-i]=1;
        while (k)
        {
       	    if (k&1) Mul1();
       	    k>>=1;
       	    Mul2();
        }
        for (i=0;i<n-1;i++) printf("%I64d ",init[i]);
        printf("%I64d\n",init[n-1]);
    }
    return 0;
}
