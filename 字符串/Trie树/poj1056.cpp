#include<stdio.h>
#include<string.h>

#define CharsetSize 2       //字符集大小
#define CharsetBase '0'     //字符集最小字符

#define MaxN 101

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
    int flag,t;
    char s[10];
    freopen("poj1056.txt","r",stdin);
    freopen("poj1056ans.txt","w",stdout);
    for (t=1;scanf("%s",s)!=EOF;t++)
    {
	TrieInit();
	Insert(s);
	flag=1;
	while (scanf("%s",s) && s[0]!='9') if (!Insert(s)) flag=0;
        if (flag) printf("Set %d is immediately decodable\n",t);
        else  printf("Set %d is not immediately decodable\n",t);
    }
    return 0;
}
