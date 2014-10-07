#include<stdio.h>
int main()
{
    int n,sum,i,a;
    while(scanf("%d",&n)&&n)
    {
        sum=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&a);
            sum=sum^a;
        }
        printf(sum==0?"Grass Win!\n":"Rabbit Win!\n");
    }
    return 0;
}
