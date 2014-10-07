#include<stdio.h>

int main()
{
    int i,j,n,p,q,swap,len,k;
    int a[30],max;
    freopen("hdoj3595.txt","r",stdin);
    freopen("hdoj3593ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        max=0;
        while (n--)
        {
            scanf("%d%d",&p,&q);
            if (p==0 || q==0) continue;
            if (q>p)
            {
               swap=p;
               p=q;
               q=swap;
            }
            a[1]=p;
            a[2]=q;
            len=2;
            while (a[len])
            {
                a[len+1]=a[len-1]%a[len];
                len++;
            }
            k=len-2;
            j=-1;
            for (i=1;i<len-1;i++) 
                if (a[i]/a[i+1]>1)
                {
                    if (j>0 && i%2!=j%2) k++;
                    j=i;
                }
            if (k>max) max=k;
        }
        if (max%2==0) printf("GG\n"); else printf("MM\n");
    }
    return 0;
}
