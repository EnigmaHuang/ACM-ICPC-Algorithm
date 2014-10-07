#include<stdio.h>

int main()
{
    int t,i,n,ans,m,l;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        ans=0;
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&m,&l);
            ans=ans^(m%(l+1));
        }
        if (ans==0) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
