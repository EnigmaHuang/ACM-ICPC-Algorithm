#include<stdio.h>
#include<string.h>
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 200005

char str[MaxN];
int  slen;

void Prepare(char *s)
{
    int i=0,k=1,t=0;
    str[0]='$';
    while (s[i])
    {
        str[k++]=t?s[i++]:'#';
        t^=1;
    }
    str[k++]='#';
    str[k]='\0';
    slen=k;
}

void Manacher(char *s,int *len)
{
    int mx=0,id,i;
    Prepare(s);
    memset(len,0,sizeof(len));
    for (i=1;i<slen;i++)
    {
        if (mx>i) len[i]=Min(len[2*id-i],mx-i);
        else len[i]=1;
        while (str[i-len[i]]==str[i+len[i]]) len[i]++;
        if (i+len[i]>mx)
        {
            mx=i+len[i];
            id=i;
        }
    }
}

char s[MaxN];
int  len[MaxN];

int main()
{
    int max,i;
    freopen("hdoj3068.txt","r",stdin);
    freopen("hdoj3068ans.txt","w",stdout);
    while (scanf("%s",s)!=EOF)
    {
        Manacher(s,len);
        max=0;
        for (i=0;i<slen;i++) if (max<len[i]-1) max=len[i]-1;
        printf("%d\n",max);
    }
}
