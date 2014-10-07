#include<stdio.h>
#include<string.h>

#define MaxN 10005
#define MaxL 80

int next[MaxN];
char s[MaxN][MaxL],revs[MaxL][MaxN];

int n,m;

void GetNext(int len)
{
    int i,j;
    memset(next,0,sizeof(next));
    next[0]=-1;
    for (i=1;i<len;i++)
    {
        j=i;
	while (j>0)
	{
	    j=next[j];
	    if (strcmp(s[j],s[i])==0)
            {
                next[i+1]=j+1;
                break;
            }
	}
    }
}

void GetNextRev(int len)
{
    int i,j;
    memset(next,0,sizeof(next));
    next[0]=-1;
    for (i=1;i<len;i++)
    {
	j=i;
        while (j>0)
	{
	    j=next[j];
	    if (strcmp(revs[j],revs[i])==0)
            {
                next[i+1]=j+1;
                break;
            }
	}
    }
}

int Reverse(int r,int c)
{
    int i,j;
    for (i=0;i<c;i++)
    {
        for (j=0;j<r;j++) revs[i][j]=s[j][i];
        revs[i][r]='\0';
    }
}

int main()
{
    int r,c,i,len,revlen;
    freopen("poj2185.txt","r",stdin);
    freopen("poj2185ans.txt","w",stdout);
    while (scanf("%d%d",&r,&c)!=EOF)
    {
	for (i=0;i<r;i++) scanf("%s",s[i]);
	GetNext(r);
	len=r-next[r];
	Reverse(r,c);
	GetNextRev(c);
	revlen=c-next[c];
	printf("%d\n",len*revlen);
    }
    return 0;
}
