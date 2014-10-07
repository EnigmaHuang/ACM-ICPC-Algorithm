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
    int n,t,len,sectlen;
    freopen("hdoj3746.txt","r",stdin);
    freopen("hdoj3746ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%s",s);
        GetNext(s);
        len=strlen(s);
        sectlen=len-next[len];
        if (next[len]!=0 && len%sectlen==0) printf("0\n");
        else printf("%d\n",sectlen-next[len]%sectlen);
    }
    return 0;
}
