#include<stdio.h>
#include<string.h>
#define MaxN 10001

int prime[MaxN],p[MaxN],cnt,len;
int num[10],ans,seq[10];

int IsPrime(int x)
{
    int i;
    if (x<MaxN) return p[x];
    for (i=1;prime[i]*prime[i]<=x;i++) if (x%prime[i]==0) return 0;
    return 1;
}

void MakePrimeList()
{
    int i,j;
    cnt=0;
    for (i=0;i<MaxN;i++) p[i]=1;
    p[0]=p[1]=0;
    for (i=2;i<MaxN;i++)
    {
        if (!p[i]) continue;
        for (j=i+i;j<MaxN;j+=i) p[j]=0;
    }
    for (i=2;i<MaxN;i++) if (p[i]) prime[++cnt]=i;
}

int NowSeqIsPrime(int pos)
{
    int x=0,i;
    for (i=pos-1;i>=0;i--) x=x*10+seq[i];
    return IsPrime(x);
}

void DFS(int pos)
{
    int i;
    if (seq[pos-1] && NowSeqIsPrime(pos)) ans++;
    if (pos==len) return;
    for (i=0;i<10;i++) if (num[i])
    {
        num[i]--;
        seq[pos]=i;
        DFS(pos+1);
        num[i]++;
    }
}

int main()
{
    int t,i;
    char s[10];
    freopen("poj3842.txt","r",stdin);
    freopen("poj3842ans.txt","w",stdout);
    scanf("%d",&t);
    MakePrimeList();
    while (t--)
    {
        scanf("%s",s);
        len=strlen(s);
        memset(num,0,sizeof(num));
        for (i=0;s[i];i++) num[s[i]-'0']++;
        ans=0;
        for (i=0;i<10;i++) if (num[i] && i%2==1) //剪枝，个位的搜索直接用奇数 
        {
       	    num[i]--;
       	    seq[0]=i;
       	    DFS(1);
       	    num[i]++;
        }
        if (num[2]) ans++; //按前面的搜索方法2没有被搜到，补上 
        printf("%d\n",ans);
    }
    return 0;
}
