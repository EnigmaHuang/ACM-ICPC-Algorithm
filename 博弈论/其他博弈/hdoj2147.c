#include<stdio.h>
int n,m;
int main()
{
    while (scanf("%d%d",&n,&m)!=EOF && n && m)
    {
        if (n%2==0 || m%2==0) printf("Wonderful!\n");
        else printf("What a pity!\n");
    }
    return 0;
}
