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

void strcopy(char *src,char *dst,int start,int end)
{
    int k=0,i;
    for (i=start;i<=end;i++) dst[k++]=src[i];
    dst[k]='\0';
}

int main()
{
    int len,i,sslen,ans,t=0;
    freopen("poj1961.txt","r",stdin);
    freopen("poj1961ans.txt","w",stdout);
    while (scanf("%d",&len)!=EOF && len)
    {
	scanf("%s",s);
	printf("Test case #%d\n",++t);
	GetNext(s);
	for (i=2;i<=len;i++)
	    if (next[i]!=0 && i%(i-next[i])==0)
	        printf("%d %d\n",i,i/(i-next[i]));
	printf("\n");
    }
    return 0;
}
