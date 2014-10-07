#include<stdio.h>

int main()
{
    int c,cases=0,n,i;
    long long a,b,x,y;
    freopen("hdoj3544.txt","r",stdin);
    freopen("hdoj3544ans.txt","w",stdout);
    scanf("%d",&c);
    while (c--)
    {
        scanf("%d",&n);
        a=b=0;
        for (i=0;i<n;i++)
        {
            scanf("%I64d%I64d",&x,&y);
            while (x>1 && y>1)
            {
                x=x>>1;
                y=y>>1;
            }
            if (x==1) b+=y-1; //一方切完另一方没切完，还可以多切几刀 
            if (y==1) a+=x-1;
            
        }
        printf("Case %d: ",++cases);
        if (a>b) printf("Alice\n"); else printf("Bob\n");
    }
    return 0;
}
