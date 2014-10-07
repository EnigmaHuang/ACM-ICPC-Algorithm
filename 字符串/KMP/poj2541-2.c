#include<stdio.h>
#include<string.h>
#define MaxN 1100000

int next[MaxN],n,l,len;
char s[MaxN],revs[MaxN];

char GetNext(char *pattern,int len)
{
    int i=0,j=-1;
    int maxx=0,maxi;
    next[0]=-1;
    while (i<len)
    {
        if (j == -1 || pattern[i]==pattern[j])
        {
            i++;
            j++;
            next[i]=j;
        }
        else j=next[j];

        if (next[i]<=13 && maxx<next[i])
        {
            maxx=next[i];
            maxi=i-next[i]-1;
        }
        if (next[i]>13) break;

    }
    
    /*
    for (i=0;i<len;i++) if (next[i]>maxx && next[i]<=13)
    {
	maxx=next[i];
	maxi=i-next[i]-1;
    }
    else if (next[i]>13) break;
    
    printf("%d\n",maxi);*/
    if (maxx==0) return '0';
    else return pattern[maxi];
}

void Reverse(char *src,char *dst,int len)
{
    int i;
    for (i=0;i<len;i++) dst[i]=src[len-i-1];
}

int main()
{
    int i,j,k;
    freopen("poj2541.txt","r",stdin);
    freopen("poj2541ans-2.txt","w",stdout);
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
