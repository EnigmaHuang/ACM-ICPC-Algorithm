#include<stdio.h>
#include<string.h>

#define MaxPL 10005
#define MaxTL 1000005

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

int res[MaxTL];
char pat[MaxPL],text[MaxTL];

int main()
{
    int t;
    freopen("poj3461.txt","r",stdin);
    freopen("poj3461ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%s%s",pat,text);
        KMP(pat,text,res);
        printf("%d\n",res[0]);
    }
    return 0;
}
