#include<stdio.h>
#include<math.h>
#define eps 0.000001

int main()
{
    double l,n,c,h,r,s,high,low,mid;
    freopen("poj1905.txt","r",stdin);
    freopen("poj1905ans.txt","w",stdout);
    while (scanf("%lf%lf%lf",&l,&n,&c)!=EOF)
    {
        if (l<0 && n<0 && c<0) break;
        s=(1+n*c)*l;
        low=0;high=l;
        while (high-low>eps)
        {
       	    mid=(high+low)/2;
       	    //fprintf(stderr,"l=%.6f,r=%.6f,mid=%.6f\n",low,high,mid);
            r=((mid*mid*4)+l*l)/(8*mid);
       	    if ((2*r*asin(l/(2*r)))<s) low=mid;else high=mid;
        }
        printf("%.3f\n",mid);
        //fprintf(stderr,"ans=%.3f\n",mid);
    }
    return 0;
}
