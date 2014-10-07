#include<stdio.h>
#include<math.h>
#define pi 3.141592653589793

int main()
{
    double s,r,h,v;
    while(scanf("%lf",&s)!=EOF)
    {
        r=sqrt(s/pi)/2;
        h=sqrt((s*s)/(pi*pi*r*r)-2*s/pi);
        v=pi*r*r*h/3;
        printf("%.2f\n%.2f\n%.2f\n",v,h,r);
    }
    return 0;
}
