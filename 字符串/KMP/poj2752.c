#include<stdio.h>
#include<string.h>

#define MaxPL 400005

int next[MaxPL],ans[MaxPL];
char s[MaxPL];

void GetNext(char *pattern)
{
    int n,i,j;
    memset(next,0,sizeof(next));
    n=strlen(pattern);
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
}

int main()
{
    int n,i,len;
    freopen("poj2752.txt","r",stdin);
    freopen("poj2752ans.txt","w",stdout);
    while (scanf("%s",s)!=EOF)
    {
        len=strlen(s);
        GetNext(s);
        n=0;
        i=len;
        ans[0]=len;    //这个也要算上！这里挂了一次
        while (next[i]>0)
        {
	    ans[++n]=next[i];
	    i=next[i];
        }
        for (i=n;i>=0;i--) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
