#include<stdio.h>
#include<string.h>
#define MaxN 1000000

int sg[MaxN];

int len(int n)
{
    if (n/100000) return 6;
    if (n/10000)  return 5;
    if (n/1000)   return 4;
    if (n/100)    return 3;
    if (n/10)     return 2;
    return 1;
}

void mex(int n)
{
    int l,i,j,m,t,a;
    l=len(n);
    for (i=l;i>0;i--)  //1、把其中一个数变为比它小的数；
    {
        m=1;
        for (j=1;j<i;j++) m*=10;
        t=(n%(m*10))/m;
        for (j=1;j<=9-t;j++) sg[n+m*j]=1;
    }
    if (l<6)   //2、把其中一个数字0及其右边的所以数字删除。
    {
        m=n;
        a=1;
        for (i=1;i<=6-l;i++)
        {
            m*=10;
            for (j=0;j<a;j++) sg[m+j]=1;
            a*=10;
        }
    }
}

int main()
{
    int n,l,i;
    char s[7];
    
    freopen("hdoj1404.txt","r",stdin);
    freopen("hdoj1404ans.txt","w",stdout);
    
    memset(sg,0,sizeof(sg));
    sg[0]=1;
    for (i=1;i<MaxN;i++) if(!sg[i]) mex(i);

    while (scanf("%s",s)!=EOF)
    {
        if (s[0]=='0')
        {
            printf("Yes\n");
            continue;
        }
        l=strlen(s);
        n=s[0]-'0';
        for (i=1;i<l;i++) n=n*10+s[i]-'0';
        if (sg[n]) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}
