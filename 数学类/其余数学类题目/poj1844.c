#include<stdio.h>

int main()
{
    int s,sum,i;
    freopen("poj1844.txt","r",stdin);
    freopen("poj1844ans.txt","w",stdout);
    while (scanf("%d",&s)!=EOF)
    {
        sum=0;
        for (i=1;i<=s;i++) 
        {
       	    sum+=i;
       	    if (sum>=s && (sum-s)%2==0)
            {
       	        printf("%d\n",i);
               	break;
            }
        }
    }
    return 0;
}
