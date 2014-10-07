#include<stdio.h>

int main()
{
    int n,m,i,j,k;
    while (scanf("%d",&n)!=EOF)
    {
        k=2;
        j=0;
        for (i=2;;i++)
        {
            if ((2*n+i-i*i)/(2*i)<=0) break;
            if ((2*n+i-i*i)%(2*i)==0) j++;
        }
        printf("%d\n",j);
    }
    return 0;
}

