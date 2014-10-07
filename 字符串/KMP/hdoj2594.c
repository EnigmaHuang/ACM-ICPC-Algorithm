#include<stdio.h>
#include<string.h>

#define MaxPL 100005

int next[MaxPL];
char s[MaxPL],s2[MaxPL/2];

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
    int i,len,len1,len2,minlen;
    freopen("hdoj2594.txt","r",stdin);
    freopen("hdoj2594ans.txt","w",stdout);
    while (scanf("%s%s",s,s2)!=EOF)
    {
	strcat(s,s2);
	GetNext(s);
	len=strlen(s);
	len2=strlen(s2);
	len1=len-len2;
	minlen=len1<len2?len1:len2;
	i=next[len];
	while (i>minlen && i>0) i=next[i];
	s[i]='\0';
	if (i!=0) printf("%s %d\n",s,i);
	else printf("0\n");
    }
    return 0;
}
