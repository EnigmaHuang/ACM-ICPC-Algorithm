#include<stdio.h>

int main()
{
    int n,m,i;
    while (scanf("%d%d",&m,&n)!=EOF)
    {
        if (m%(n+1)==0) printf("none\n");
        else if (m<=n)
        {
            printf("%d",m);
            for (i=m+1;i<=n;i++) printf(" %d",i);
            printf("\n");
        }
        else printf("%d\n",m%(n+1));
    }
    return 0;
}
