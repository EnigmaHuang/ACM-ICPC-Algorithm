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
    int n,cases=0,i,sectlen;
    freopen("hdoj1358.txt","r",stdin);
    freopen("hdoj1358ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
	scanf("%s",s);
	GetNext(s);
	printf("Test case #%d\n",++cases);
	for (i=1;i<=n;i++)
	{
	    sectlen=i-next[i];
	    if (i%sectlen==0 && i/sectlen>1) printf("%d %d\n",i,i/sectlen);
	}
	printf("\n");
    }
    return 0;
}
