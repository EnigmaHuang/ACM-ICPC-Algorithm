#include<stdio.h>
#include<string.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 200005

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

int  next[MaxN],extend[MaxN],sectlen,len;
char s1[MaxN],s2[MaxN];

void GetKMPNext(char *pattern)
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
    sectlen=n-next[n];
}

void Solve()
{
    int i,less,equ,greater;
    if (len%sectlen!=0) sectlen=len;
    less=equ=greater=0;
    /*
    extend[i]：第i位作为起始的后缀（位移为i）能匹配的原串前缀长度
    s2[i]：位移为i得到的串的第一位
    s2[extend[i]]：位移为i，所匹配的原串的长度后一位
    s2[extend[i]+i]：位移为i，所匹配的原串的长度后一位，对应的位移串长度后一位
    */
    for (i=0;i<sectlen;i++)
    {
	//s2[i~i+len-1]与s1完全匹配，则这个位移量的结果相等
	if (extend[i]==len) equ++;
	//位移串失配位置的值小于原串失配位置的值
	else if (s2[extend[i]]>s2[i+extend[i]]) less++;
        //位移串失配位置的值大于原串失配位置的值
	else if (s2[extend[i]]<s2[i+extend[i]]) greater++;
    }
    printf("%d %d %d\n",less,equ,greater);
}

int main()
{
    int t,i,n;
    freopen("hdoj4333.txt","r",stdin);
    freopen("hdoj4333ans.txt","w",stdout);
    scanf("%d\n",&t);
    for (i=1;i<=t;i++)
    {
	scanf("%s",s1);
	strcpy(s2,s1);
	strcat(s2,s1);  
	len=strlen(s1);
	GetKMPNext(s1);
	ExtendedKMP(s1,s2,next,extend);
	printf("Case %d: ",i);
	Solve();
    }
    return 0;
}
