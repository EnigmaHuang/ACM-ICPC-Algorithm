#include<stdio.h>
#include<string.h>

#define MaxPL 1000005
#define MaxTL 1000005

int pat[MaxPL],text[MaxTL],patlen,txtlen;
int next[MaxPL];

int KMP()
{
    int n,m,i,j;
    memset(next,0,sizeof(next));
    n=patlen;
    m=txtlen;
    //È¡nextº¯ÊýÖµ
    for (i=1;i<n;i++)
    {
        j=i;
        while (j>0)
        {
            j=next[j];
            if (pat[j]==pat[i])
            {
                next[i+1]=j+1;
                break;
            }
        }
    }
    //KMPÆ¥Åä
    for (i=0,j=0;i<m;i++)
    {
        if (j<n && text[i]==pat[j]) j++;
        else while (j>0)
        {
            j=next[j];
            if (text[i]==pat[j])
            {
                j++;
                break;
            }
        }
        if (j==n) return i-n+1;
    }
    return -1;
}

int main()
{
    int n,t,i,ans;
    freopen("hdoj1711.txt","r",stdin);
    freopen("hdoj1711ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
	scanf("%d%d",&txtlen,&patlen);
	for (i=0;i<txtlen;i++) scanf("%d",&text[i]);
	for (i=0;i<patlen;i++) scanf("%d",&pat[i]);
	ans=KMP();
	if (ans>=0) printf("%d\n",ans+1); else printf("-1\n");
    }
}
