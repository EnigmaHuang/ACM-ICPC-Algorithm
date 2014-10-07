#include<stdio.h>
#include<string.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 100005

/*
求a（模板串）关于b（主串）的每个后缀的最长公共前缀
ANext[i]:a[i~M]和a的最长公共前缀长度
BRes[i] :b[i~N]和a的最长公共前缀长度
*/
void ExtendedKMP(char *a,char *b,int *ANext,int *BRes)
{
    int i,j,k,M,N,Len,L;
    M=strlen(a);
    N=strlen(b);
    for (j=0;j+1<M && a[j]==a[j+1];j++);
    ANext[1]=j;
    k=1;
    for (i=2;i<M;i++)
    {
        Len=k+ANext[k];
        L=ANext[i-k];
        if (L+i<Len) ANext[i]=L;
        else
        {
            for (j=Max(0,Len-i);i+j<M && a[j]==a[i+j];j++);
            ANext[i]=j;
            k=i;
        }
    }
    for (j=0;j<N && j<M && a[j]==b[j];j++);
    BRes[0]=j;
    k=0;
    for (i=1;i<N;i++)
    {
        Len=k+BRes[k];
        L=ANext[i-k];
        if (L<Len-i) BRes[i]=L;
        else
        {
            for (j=Max(0,Len-i);j<M && i+j<N && a[j]==b[i+j];j++);
            BRes[i]=j;
            k=i;
        }
    }
}

int  next[MaxN],extend[MaxN];
char s1[MaxN],s2[MaxN],s1s2[MaxN*2],s2s1[MaxN*2];

int main()
{
    int len1,len2,repeat1,repeat2,i;
    freopen("hdoj1867.txt","r",stdin);
    freopen("hdoj1867ans.txt","w",stdout);
    while (scanf("%s%s",s1,s2)!=EOF)
    {
	len1=strlen(s1);
	len2=strlen(s2);
	
	ExtendedKMP(s1,s2,next,extend);
	repeat2=0;
	for (i=0;i<len2;i++) if (i+extend[i]==len2)
	{
	    repeat2=extend[i];
	    break;
        }

	ExtendedKMP(s2,s1,next,extend);
        repeat1=0;
	for (i=0;i<len1;i++) if (i+extend[i]==len1)
	{
	    repeat1=extend[i];
	    break;
        }
        
        strcpy(s1s2,s1);
        s1s2[len1-repeat1]='\0';
        strcat(s1s2,s2);
        
        strcpy(s2s1,s2);
        s2s1[len2-repeat2]='\0';
        strcat(s2s1,s1);
        
        if (repeat1==repeat2)
        {
	    if (strcmp(s1s2,s2s1)<0) printf("%s\n",s1s2);
	    else printf("%s\n",s2s1);
        }
        else if (repeat1>repeat2) printf("%s\n",s1s2);
        else if (repeat2>repeat1) printf("%s\n",s2s1);
    }
    return 0;
}
