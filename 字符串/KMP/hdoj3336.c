#include<stdio.h>
#include<string.h>

#define MaxPL 200005

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

int dp[MaxPL];

int main()
{
    int t,len,i,ans;
    freopen("hdoj3336.txt","r",stdin);
    freopen("hdoj3336ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
	scanf("%d",&len);
	scanf("%s",s);
	GetNext(s);
	ans=dp[0]=0;
	for (i=1;i<=len;i++)
	{
	    dp[i]=dp[next[i]]+1;
	    ans+=dp[i];
	    ans%=10007;
	}
	printf("%d\n",ans);
    }
    return 0;
}
