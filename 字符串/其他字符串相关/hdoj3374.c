#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 1000001

int next[MaxN];

void GetNext(char *pattern)
{
    int n,i,j;
    memset(next,0,sizeof(next));
    n=strlen(pattern);
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

char s[MaxN*2];

int SmallestRepresation(char* src)
{
    int i,j,k,l,len;
    len=strlen(src);
    strcpy(s,src);
    strcat(s,src);
    i=0;j=1;
    while (j<len)
    {
        for (k=0;k<len && s[i+k]==s[j+k];k++);
        if (k>=len) break;
        if (s[i+k]<s[j+k]) j+=k+1;
        else
        {
            l=i+k;
            i=j;
            j=Max(l,j)+1;
        }
    }
    return i+1;
}

int LargestRepresation(char* src)
{
    int i,j,k,l,len;
    len=strlen(src);
    strcpy(s,src);
    strcat(s,src);
    i=0;j=1;
    while (j<len)
    {
        for (k=0;k<len && s[i+k]==s[j+k];k++);
        if (k>=len) break;
        if (s[i+k]>s[j+k]) j+=k+1;
        else
        {
            l=i+k;
            i=j;
            j=Max(l,j)+1;
        }
    }
    return i+1;
}

char str[MaxN];

int main()
{
    int len,sectlen,ans,min,max;
    freopen("hdoj3374.txt","r",stdin);
    freopen("hdoj3374ans.txt","w",stdout);
    while (scanf("%s",str)!=EOF)
    {
        len=strlen(str);
        min=SmallestRepresation(str);
        max=LargestRepresation(str);
        GetNext(str);
        sectlen=len-next[len];
        ans=(len%sectlen)?1:(len/sectlen);
        printf("%d %d %d %d\n",min,ans,max,ans);
    }
    return 0;
}
