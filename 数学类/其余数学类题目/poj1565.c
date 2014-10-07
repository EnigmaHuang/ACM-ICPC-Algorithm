#include<stdio.h>
#define MaxN 35

long long skewpow[MaxN];

int main()
{
    long long i,ans,pos,pow2=1;
    char s[MaxN];
    freopen("poj1565.txt","r",stdin);
    freopen("poj1565ans.txt","w",stdout);
    for (i=0;i<MaxN;i++)
    {
        pow2*=2;
        skewpow[i]=pow2-1;
        fprintf(stderr,"%lld\n",skewpow[i]); 
    }
    while (scanf("%s",s)!=EOF)
    {
        if (s[0]=='0' && s[1]==0) break;
        ans=pos=0;
        for (i=0;s[i];i++);
	for (i--;i>=0;i--) 
	{
	    ans+=skewpow[pos++]*(s[i]-'0');
	    fprintf(stderr,"%c %lld \n",s[i],skewpow[pos]*(s[i]-'0'));
	    fprintf(stderr,"%lld\n\n",ans);   
	}
        printf("%lld\n",ans);
    }
    return 0;
}
