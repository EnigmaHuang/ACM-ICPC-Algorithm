#include<stdio.h>
#include<string.h>

#define RKPrime        13747347
#define MaxCharsetSize 255
#define MaxN           16000005

int base[MaxCharsetSize];
int hash[RKPrime];

void InitRK(char *s,int len)
{
    int i,x=0;
    memset(base,0,sizeof(base));
    for (i=0;i<len;i++) base[s[i]]=1;
    for (i=0;i<MaxCharsetSize;i++) if (base[i]) base[i]=x++;
    memset(hash,0,sizeof(hash));
}

int Query(char *s,int n,int nbase)
{
    int num=0,i;
    for (i=0;i<n;i++) num=(nbase*num+base[s[i]])%RKPrime;
    if (!hash[num])
    {
        hash[num]=1;
        return 1;
    }
    else return 0;
}

char s[MaxN];

int main()
{
    int n,nc,i,len,ans;
    freopen("poj1200.txt","r",stdin);
    freopen("poj1200ans.txt","w",stdout);
    while (scanf("%d %d %s",&n,&nc,s)!=EOF)
    {
        len=strlen(s);
        InitRK(s,len);
        ans=0;
        for (i=0;i<len-n+1;i++) ans+=Query(s+i,n,nc);
        printf("%d\n",ans);
    }
    return 0;
}
