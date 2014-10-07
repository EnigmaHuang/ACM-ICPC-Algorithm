#include<stdio.h>
#include<string.h>

#define MaxPL 105
#define MaxTL 105
#define MaxN  105

void KMP(char *pattern,char *text,int res[])
{
    int n,m,i,j;
    int next[MaxPL];
    memset(next,0,sizeof(next));
    n=strlen(pattern);
    m=strlen(text);
    //È¡nextº¯ÊýÖµ
    for (i=1;i<n;i++)
    {
        j=i;
        while (j>0)
        {
            j=next[j];
            if (pattern[j]==pattern[i])
            {
                next[i+1]=j+1;
                break;
            }
        }
    }
    //KMPÆ¥Åä
    res[0]=0;
    for (i=0,j=0;i<m;i++)
    {
        if (j<n && text[i]==pattern[j]) j++;
        else while (j>0)
        {
            j=next[j];
            if (text[i]==pattern[j])
            {
                j++;
                break;
            }
        }
        if (j==n)
        {
            res[0]++;
            res[res[0]]=i-n+1;
        }
    }
}

int res1[MaxTL],res2[MaxTL];
char pat1[MaxPL],pat2[MaxPL],text[MaxTL];
char s[MaxN][MaxPL];

void strcopy(char *src,char *dst,int start,int end)
{
    int k=0,i;
    for (i=start;i<=end;i++) dst[k++]=src[i];
    dst[k]='\0';
}

int main()
{
    int t,n,i,j,k,len,sslen,maxlen;
    freopen("poj1226.txt","r",stdin);
    freopen("poj1226ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++) scanf("%s",s[i]);
        len=strlen(s[0]);
        maxlen=0;
        for (i=0;i<len;i++)
        {
            for (j=i;j<len;j++)
            {
                strcopy(s[0],pat1,i,j);
                sslen=strlen(pat1);
                for (k=0;k<sslen;k++) pat2[k]=pat1[sslen-1-k];
                pat2[k]='\0';
                for (k=1;k<n;k++)
                {
                    KMP(pat1,s[k],res1);
                    KMP(pat2,s[k],res2);
                    if (res1[0]==0 && res2[0]==0) break;
                }
                if (k==n) maxlen=maxlen>sslen?maxlen:sslen;
            }
        }
        printf("%d\n",maxlen);
    }
    return 0;
}
