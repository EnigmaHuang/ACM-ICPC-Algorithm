#include<stdio.h>

#define MaxN 2000000

int a[MaxN],b[MaxN];

int main()
{
    int n,k,i,j,cases,t=0,last;
    freopen("poj3922.txt","r",stdin);
    freopen("poj3922ans.txt","w",stdout);
    scanf("%d",&cases);
    while (cases--)
    {
        scanf("%d%d",&n,&k);
        i=j=0;
        a[0]=b[0]=1;
        while (a[i]<n)
        {
            i++;
            a[i]=b[i-1]+1;
            while (a[j+1]*k<a[i]) j++;
            if (a[j]*k<a[i]) b[i]=a[i]+b[j];
            else b[i]=a[i];
        }
        printf("Case %d: ",++t);
        if (a[i]==n) printf("lose\n");
        else
        {
            last=-1;
            while (n)
            {
                if (n>=a[i])
                {
                    last=a[i];
                    n-=a[i];
                }
                i--;
            }
            printf("%d\n",last);
        }
    }
    return 0;
}
