#include<stdio.h>
#include<string.h>

#define MaxPL 1005
#define MaxTL 1005

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
            j=0;  //不等待回溯，直接指向头部重新匹配
        }
    }
}

int res[MaxTL];
char pat[MaxPL],text[MaxTL];

int main()
{
    freopen("hdoj2087.txt","r",stdin);
    freopen("hdoj2087ans.txt","w",stdout);
    while (scanf("%s",text)!=EOF)
    {
        if (text[0]=='#') break;
        scanf("%s",pat);
        KMP(pat,text,res);
	printf("%d\n",res[0]);
    }
     return 0;
}
