#include<stdio.h>
#include<string.h>

#define MaxPL 100005
#define MaxTL 100005

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
    int i,txtlen,patlen;
    freopen("hdoj2203.txt","r",stdin);
    freopen("hdoj2203ans.txt","w",stdout);
    while (scanf("%s",text)!=EOF)
    {
	scanf("%s",pat);
	txtlen=strlen(text);
	patlen=strlen(pat);
	if (txtlen<patlen)
	{
            printf("no\n");
            continue;
	}
	for (i=0;i<patlen;i++) text[txtlen+i]=text[i];
	txtlen+=patlen;
	text[txtlen]='\0';
	KMP(pat,text,res);
	if (res[0]>0) printf("yes\n"); else printf("no\n");
    }
    return 0;
}
