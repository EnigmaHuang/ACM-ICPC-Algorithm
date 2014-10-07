#include<stdio.h>
#include<string.h>

#define MaxPL 1000005

int next[MaxPL];
char s[MaxPL];

void GetNext(char *pattern)
{
    int n,i,j;
    memset(next,0,sizeof(next));
    n=strlen(pattern);
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
}

int main()
{
    int n,ans,len;
    freopen("poj2406.txt","r",stdin);
    freopen("poj2406ans.txt","w",stdout);
    while (scanf("%s",s)!=EOF)
    {
	if (s[0]=='.') break;
	len=strlen(s);
	GetNext(s);
	ans=1;
	if (len%(len-next[len])==0) ans=len/(len-next[len]);
	printf("%d\n",ans);
    }
    return 0;
}
