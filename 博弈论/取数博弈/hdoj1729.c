#include<stdio.h>
#include<math.h>

int SG(int s,int c)
{
    int q=sqrt(1.0*s);
    while (q+q*q>=s) q--;
    if (c>q) return s-c;
    else return SG(q,c);
}

int main()
{
    int n,t=0,s,c,ans;
    while (scanf("%d",&n)!=EOF && n)
    {
        ans=0;
        while (n--)
        {
            scanf("%d%d",&s,&c);
            ans^=SG(s,c);
        }
        printf("Case %d:\n",++t);
        if (ans) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
