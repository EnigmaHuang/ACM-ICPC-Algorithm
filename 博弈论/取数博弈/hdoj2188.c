#include<stdio.h>

int main()
{
    int n,m,t;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        if (n%(m+1)==0) printf("Rabbit\n"); else printf("Grass\n");
    }
    return 0;
}
