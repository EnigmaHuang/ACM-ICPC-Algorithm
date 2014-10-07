#include<stdio.h>
#include<string.h>

#define MaxPL 1100000

int next[MaxPL];
char s[MaxPL],revs[MaxPL];

char GetNext(char *pattern,int len)
{
    int n,i,j,maxi,maxn;
    memset(next,0,sizeof(next));
    n=strlen(pattern);
    maxn=0;
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
        if (next[i]>13) break;
    }
    for (i=1;i<n;i++) if (next[i]>maxn && next[i]<=13)
    {
	maxn=next[i];
	maxi=i-next[i]-1;
    }
    else if (next[i]>13) break;
    printf("%d\n",maxi);
    if (maxn==0) return '0'; else return pattern[maxi];
}

void Reverse(char *src,char *dst,int len)
{
    int i;
    for (i=0;i<len;i++) dst[i]=src[len-i-1];
}

int main()
{
    int n,l,i,len;
    freopen("poj2541.txt","r",stdin);
    freopen("poj2541ans.txt","w",stdout);
    while (scanf("%d%d",&n,&l)!=EOF)
    {
	scanf("%s",s);
	for (i=0;i<l;i++)
	{
	    len=n+i;
	    Reverse(s,revs,len);
	    s[len]=GetNext(revs,len);
	}
        for (i=n;i<l+n;i++) printf("%c",s[i]);
        printf("\n");
    }
    return 0;
}
