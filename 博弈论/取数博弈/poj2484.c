#include<stdio.h>

int main()
{
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        if (n<=2) printf("Alice\n"); else printf("Bob\n");
    }
    return 0;
}
