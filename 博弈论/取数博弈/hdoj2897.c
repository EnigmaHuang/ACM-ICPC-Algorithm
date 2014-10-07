#include <stdio.h>

int main()
{
    int n,p,q;
    while(scanf("%d%d%d",&n,&p,&q)!=EOF)
    {
        n=n%(p+q);
        if (n>0 && n<=p)printf("LOST\n");
        else printf("WIN\n");
    }
    return 0;
}

