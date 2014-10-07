#include<stdio.h>
#include<math.h>

int main()
{
    int n,m,k,ans,i,a,b,tmp;
    freopen("hdoj2177.txt","r",stdin);
    freopen("hdoj2177ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m))
    {
        if (n==0 && m==0) break;
        k=m-n;
        ans=floor(k*(1.0+sqrt(5.0))/2.0);
        if (ans!=n)
        {
            printf("1\n");
            k=n-ans;
            printf("%d %d\n",n-k,m-k);
            for (i=m-1;i>=0;i--)
            {
                a=n;
                b=i;
                if (a>b)
                {
                   tmp=a;
                   a=b;
                   b=tmp;
                }
                k=b-a;
                ans=floor(k*(1.0+sqrt(5.0))/2.0);
                if (ans==a)
                {
                    printf("%d %d\n",a,b);
                    break;
                }
            }
        }
        else printf("0\n");
    }
    return 0;
}
