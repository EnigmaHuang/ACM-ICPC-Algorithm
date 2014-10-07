#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 10001

int SmallestRepresation(char* src)
{
    int i,j,k,l,len;
    char* s;
    len=strlen(src);
    s=(char*)malloc(sizeof(char)*len*2);
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
    free(s);
    return i+1;
}

char s[MaxN];

int main()
{
    int n;
    freopen("poj1509.txt","r",stdin);
    freopen("poj1509ans.txt","w",stdout);
    scanf("%d",&n);
    while (n--)
    {
        scanf("%s",s);
        printf("%d\n",SmallestRepresation(s));
    }
    return 0;
}
