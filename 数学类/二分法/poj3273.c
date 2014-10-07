#include<stdio.h>
#define MaxN 100005 

int n,m,money[MaxN];

int Check(int mid)
{
    int i,cnt=1,w=0;
    for (i=1;i<=n;i++) 
    {
        w+=money[i];
        if (w>mid)
        {
       	    cnt++;
       	    w=money[i];
        }
    }
    if (cnt>m) return 1;else return 0;
}

int main()
{
    int i,max,sum,l,r,mid;
    freopen("poj3273.txt","r",stdin);
    freopen("poj3273ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        max=0;sum=0;
        for (i=1;i<=n;i++)
        {
       	    scanf("%d",&money[i]);
       	    if (money[i]>max) max=money[i];
       	    sum+=money[i];
        }
        l=max;r=sum;
        while (r>l)
        {
       	    mid=(l+r)/2;
       	    //fprintf(stderr,"l=%d,r=%d,mid=%d\n",l,r,mid);
       	    if (Check(mid)) l=mid+1; else r=mid-1;
        }
        printf("%d\n",r);
        //fprintf(stderr,"ans=%d\n",r); 
    }
    return 0;
}
