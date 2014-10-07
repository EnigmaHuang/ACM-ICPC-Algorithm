#include<stdio.h>
#include<math.h>

int main()
{
    int a,b,k,tmp;
    while (scanf("%d%d",&a,&b)!=EOF)
    {
        if (a>b)
        {
            tmp=a;
            a=b;
            b=tmp;
        }
        k=b-a;
        tmp=floor(k*(1.0+sqrt(5.0))/2.0);
        if (tmp==a) printf("0\n"); else printf("1\n");
    }
    return 0;
}
