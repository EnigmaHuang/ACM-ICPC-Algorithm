#include<stdio.h>
#include<string.h>

#define MaxN 1005

int main()
{
    int i,j,ans[100],len1,len2;
    int p,b,m;
    char M[MaxN],P[MaxN];
    freopen("poj2305.txt","r",stdin);
    freopen("poj2305ans.txt","w",stdout);
    while (scanf("%d",&b) && b)
    {
        scanf("%s%s",P,M);
        p=m=0;
        len1=strlen(M);
        len2=strlen(P);
        for (i=0;i<len1;i++) p=p*b+M[i]-'0';
        for (i=0;i<len2;i++)
        {
       	    m=m*b+P[i]-'0';
       	    if (m>=p) m%=p;
        }
        i=0;
        while (1)
        {
       	    ans[i++]=m%b;
       	    m/=b;
       	    if (m==0) break;
        }
        for (j=i-1;j>=0;j--) printf("%d",ans[j]);
        printf("\n");
    }
    return 0;
}
