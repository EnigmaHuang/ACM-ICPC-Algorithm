#include<stdio.h>
#include<math.h>
#define N 1005
#define M 10005
int t[N],c[M],res[M],prime[M],vis[M],cnt,n;

int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}

void cal(int s)
{
    int i,k;
    for (i=0;i<cnt && s>1;++i) if (s%prime[i]==0)
    {
        k=0;
        while(s%prime[i]==0)
        {
            s/=prime[i];
            k++;
        }
        if (k>c[prime[i]]) c[prime[i]]=k;
    }
}

void MakePrimeList(int n)
{
    int m=sqrt(n+0.5),i,j;
    for (i=2;i<=m;++i) if (!vis[i])
        for (j=i*i;j<=n;j+=i) vis[j]=1;
    cnt=0;
    for (i=2;i<=n;++i) if (!vis[i]) prime[cnt++]=i;
}

int main()
{
    int i,j,k,fm,a,b,d,index,temp;
    freopen("poj3101.txt","r",stdin);
    freopen("poj3101ans.txt","w",stdout);
    MakePrimeList(M);
    while (scanf("%d",&n)!=EOF)
    {
        for (i=1;i<=n;++i) scanf("%d",&t[i]);
        memset(c,0,sizeof(c));

        fm=0;
        for (i=2;i<=n;++i)
        {
            b=t[i]*t[1];
            a=abs(t[i]-t[1])*2;
            d=gcd(a,b);

            a/=d; //分数化简
            b/=d;
            fm=gcd(a,fm); //分母不断求最大公约数
            cal(b);
        }

        memset(res,0,sizeof(res));
        res[1]=1;
        
        //1位存4位的高精度大整数乘法
        for (i=1;i<=10000;++i)
            for (j=1;j<=c[i];++j)
            {
                temp=0;
                for (k=1;k<=N;++k)
                {
                    res[k]=res[k]*i+temp;
                    temp=res[k]/10000;
                    res[k]%=10000;
                }
            }
        index=N;
        for (;res[index]==0;index--) ;
        printf("%d",res[index--]);
        for (;index>=1;--index) printf("%04d",res[index]);
        printf(" %d\n",fm);
    }
    return 0;
}
