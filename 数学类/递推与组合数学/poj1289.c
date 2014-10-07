#include <stdio.h>
#include <math.h>
#define MaxDeep 32
#define eps 0.0000000001

int main()
{
    long long h,n,ans1,ans2,m,num,sum,num2,hei;  //n为叶结点个数，m为度
    int i;
    double d,t1,t2;  //d表示深度
    freopen("poj1289.txt","r",stdin);
    freopen("poj1289ans.txt","w",stdout); 
    while (scanf("%lld%lld",&h,&n)!=EOF)
    {
        if (h==0 && n==0) break;
        else if (n==1 && h==1) printf("0 1\n");
        else
        {
            for (d=1;d<=MaxDeep;d++)
	    {
                t1=pow(h,1.0/d);
                t2=pow(n,1.0/d);
                if(fabs(t1-t2-1)<eps) break;  //用eps来控制精度 
            }
            if (n!=1)
	    {
                m=t2+eps;    //这里很奇怪，直接用(int)t2是会出错的，一定要写成这样 
                num=(n-1)/(m-1);  
                num2=n;
                hei=1;
                sum=0;
                for (i=0;i<=d;i++)
                {
               	    sum+=num2*hei;
               	    hei*=m+1;
               	    num2/=m;
                }
            }
            else
	    {
                num=1;
                sum=0;
            }
            printf("%lld %lld\n",num,sum);
        }
    }
    return 0;
}
