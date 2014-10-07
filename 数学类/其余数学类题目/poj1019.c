#include<stdio.h>

#define MaxN 40000

long long sum[MaxN]={0,1};

int NumLen(int i)
{
    if (0<=i && i<=9)         return 1;
    if (10<=i && i<=99)       return 2; 
    if (100<=i && i<=999)     return 3;
    if (1000<=i && i<=9999)   return 4;
    if (10000<=i && i<=99999) return 5;
}

int pow10(int a)
{
    int i,res=1;
    for (i=1;i<=a;i++) res*=10;
    return res;
}

int main()
{
    int i,j,t,n;
    long long lsum,pos;
    freopen("poj1019.txt","r",stdin);
    freopen("poj1019ans.txt","w",stdout);
    lsum=1;
    for (i=2;i<=MaxN;i++) //打表求位长之和 
    {
        lsum+=NumLen(i);
        sum[i]=sum[i-1]+lsum;
    }
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        lsum=0;
        for (i=1;sum[i]<n;i++); //确定在第几组 
        lsum=n-sum[i-1];
        pos=0;
        for (j=1;j<=i;j++)      //确定在组中的位置 
        {
       	   pos+=NumLen(j);
       	   if (pos>=lsum) break;
        }
        if (pos==lsum) printf("%d\n",j%10);
        if (pos>lsum) printf("%d\n",j/pow10(pos-lsum)%10);
    }
    return 0;
} 
