#include<stdio.h>

int main()
{
    int fibo[45],i,n;
    fibo[0]=2;
    fibo[1]=3;
    for (i=2;i<45;i++) fibo[i]=fibo[i-1]+fibo[i-2];
    while (scanf("%d",&n)!=EOF && n)
    {
         for (i=0;i<45;i++) if(fibo[i]==n) break;
         if(i==45) printf("First win\n");
         else printf("Second win\n");
    }
    return 0;
}
