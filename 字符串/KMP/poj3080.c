#include<stdio.h>
#include<string.h>

#define MaxPL 65
#define MaxTL 65
#define MaxN  15

void KMP(char *pattern,char *text,int res[])
{
    int n,m,i,j;
    int next[MaxPL];
    memset(next,0,sizeof(next));
    n=strlen(pattern);
    m=strlen(text);
    //取next函数值
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
    //KMP匹配
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
char s[MaxN][MaxPL];

void strcopy(char *src,char *dst,int start,int end)
{
    int k=0,i;
    for (i=start;i<=end;i++) dst[k++]=src[i];
    dst[k]='\0';
}

int main()
{
    int t,n,i,j,k;
    char ans[MaxPL];
    freopen("poj3080.txt","r",stdin);
    freopen("poj3080ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%s",s[i]);
	ans[0]='\0';
	for (i=60;i>=3;i--) if (i>=strlen(ans))
	{
	    for (j=0;j<=60-i;j++)
	    {
	    	strcopy(s[0],pat,j,j+i-1);
	    	for (k=1;k<n;k++)
	    	{
	            KMP(pat,s[k],res);
		    if (res[0]==0) break;
	    	}
	    	if (k<n) continue;  //当前子串不符合
	    	if (strlen(ans)==0) strcpy(ans,pat);
	    	else if (strcmp(ans,pat)>0) strcpy(ans,pat);
	    }
	}
	if (strlen(ans)==0) printf("no significant commonalities\n");
	else printf("%s\n",ans);
    }
    return 0;
}
