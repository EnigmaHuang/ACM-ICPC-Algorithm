#include<stdio.h>
#include<math.h>

#define MaxN 10050
#define pi   3.14159265358 
#define eps  0.00001

double pie[MaxN];

int main()
{
    double l,r,mid,sum;
    int i,t,R,n,f,cnt;
    freopen("poj3122.txt","r",stdin);
    freopen("poj3122ans.txt","w",stdout);
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&f);
        f++;
        sum=0;
        for (i=1;i<=n;i++)
        {
       	    scanf("%d",&R);
       	    pie[i]=R*R*pi;
       	    sum+=pie[i];
        }
        l=0;r=sum/(f);
        while(r-l>eps)
        {
       	    mid=(l+r)/2;
       	    //fprintf(stderr,"l=%.4f,r=%.4f,mid=%.4f\n",l,r,mid);
       	    cnt=0;
       	    for (i=1;i<=n;i++) cnt+=floor(pie[i]/mid);
       	    if (cnt<f) r=mid;else l=mid;
        }
        printf("%.4f\n",mid);
    }
    return 0;
}
