#include<stdio.h>

int main()
{
    int t,y,m,d;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d%d",&y,&m,&d);
        if (d==30 && (m==9 || m==11)) printf("YES\n");
        else if ((m+d)%2) printf("NO\n");
             else printf("YES\n");
    }
    return 0;
}
