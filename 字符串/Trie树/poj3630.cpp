#include<stdio.h>
#include<string.h>

#define CharsetSize 10      //字符集大小
#define CharsetBase '0'     //字符集最小字符

#define MaxN 10001

struct TrieNode
{
    int flag;
    int next[CharsetSize];
}trie[MaxN*CharsetSize];

int index;

int Insert(char str[])
{
    int i,p=1,f=1,f2=0;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)   //节点不存在
        {
            trie[p].next[str[i]-CharsetBase]=++index;
            f2=1;              //创建了一个新节点
        }
        p=trie[p].next[str[i]-CharsetBase];
        if (trie[p].flag) f=0; //如果这个节点是之前某个单词的结束，有前缀
    }
    trie[p].flag=1;   //标记该点为一个单词的结束
    if (f2==0) f=0;   //如果没有创建新节点，返回0
    return f;
}

int TrieInit()
{
    index=1;
    memset(trie,0,sizeof(trie));
}

int main()
{
    int flag,t,n,i;
    char s[15];
    freopen("poj3630.txt","r",stdin);
    freopen("poj3630ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
	scanf("%d",&n);
	TrieInit();
	flag=1;
	for (i=0;i<n;i++)
	{
	    scanf("%s",s);
	    if (!Insert(s)) flag=0;
	}
        if (flag) printf("YES\n");
        else  printf("NO\n");
    }
    return 0;
}
