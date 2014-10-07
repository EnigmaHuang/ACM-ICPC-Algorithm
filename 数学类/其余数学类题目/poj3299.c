#include<stdio.h>
#include<math.h>

int main()
{
    double tem,hum,dew,num1,num2,h,e;
    char first,second;
    freopen("poj3299.txt","r",stdin);
    freopen("poj3299ans.txt","w",stdout);
    while (scanf("%c",&first) && first!='E')
    {
        scanf(" %lf %c %lf\n",&num1,&second,&num2);
        if (first=='T' && second=='D')
        {
       	    tem=num1;
       	    dew=num2;
       	    e=6.11*exp(5417.7530*(1/273.16-1.0/(dew+273.16)));
       	    h=0.5555*(e-10.0);
            hum=tem+h;
        }
        else if (first=='D' && second=='T')
        {
       	    tem=num2;
       	    dew=num1;
       	    e=6.11*exp(5417.7530*(1/273.16-1.0/(dew+273.16)));
       	    h=0.5555*(e-10.0);
       	    hum=tem+h;
        }
        else if (first=='T' && second=='H')
        {
       	    tem=num1;
       	    hum=num2;
       	    h=hum-tem;
       	    e=h/0.5555+10.0;
       	    dew=1/(-log(e/6.11)/5417.7530+1/273.16)-273.16;
        }
        else if (first=='H' && second=='T')
        {
            tem=num2;
            hum=num1;
            h=hum-tem;
            e=h/0.5555+10.0;
            dew=1/(-log(e/6.11)/5417.7530+1/273.16)-273.16;
        }
        else if (first=='D' && second=='H')
        {
            dew=num1;
            hum=num2;
            e=6.11*exp(5417.7530*(1/273.16-1.0/(dew+273.16)));
            h=0.5555*(e-10.0);
            tem=hum-h;
        }
        else if (first=='H' && second=='D')
        {
            dew=num2;
            hum=num1;
            e=6.11*exp(5417.7530*(1/273.16-1.0/(dew+273.16)));
            h=0.5555*(e-10.0);
            tem=hum-h;
        }
        printf("T %.1f D %.1f H %.1f\n",tem,dew,hum);
    }
    return 0;
}
