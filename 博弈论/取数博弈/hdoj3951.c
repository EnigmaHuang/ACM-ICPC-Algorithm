#include<stdio.h>

int main()
{
    int t,n,k,i;
    scanf("%d",&t);
    for (i=1;i<=t;i++)
    {
        scanf("%d%d",&n,&k);
        if (k>=n) printf("Case %d: first\n",i);
        else
        {
            if (k==1)
            {
               if (n%2) printf("Case %d: first\n",i);
               else printf("Case %d: second\n",i);
            }
            else printf("Case %d: second\n",i);
        }
    }
    return 0;
}
