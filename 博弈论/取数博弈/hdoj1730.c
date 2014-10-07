#include<stdio.h>

int main()
{
    int n,m,a,b,ans;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        ans=0;
        while (n--)
        {
            scanf("%d%d",&a,&b);
            ans^=(abs(a-b)-1);
        }
        if (ans) printf("I WIN!\n"); else printf("BAD LUCK!");
    }
    return 0;
}
