#include<stdio.h>

#define CharsetSize 95  //不知道为什么一定要开到95，也就是最后容忍到ascii 127
#define CharsetBase ' '

struct TrieNode
{
    int num;
    int next[CharsetSize];
}trie[10005*(2*26+1)];

int index;

void Insert (char str[])
{
    int p=1,i;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)
        {
            trie[p].next[str[i]-CharsetBase]=++index;
            trie[index].num=0;  //新建一个节点，还没被走过
        }
        p=trie[p].next[str[i]-CharsetBase];
    }
    trie[p].num++;   //标记这个单词的出现次数
}

int len,n;
char ans[35];

void PreOrder(int p)
{
    int i;
    if (trie[p].num) //已经到单词末尾了
    {
	for (i=0;i<len;i++) printf("%c",ans[i]);
	printf(" %.4f\n",trie[p].num*100.0/n);
    }
    for (i=0;i<CharsetSize;i++) if (trie[p].next[i])
    {
    	ans[len++]=CharsetBase+i;
    	PreOrder(trie[p].next[i]);
    	len--;
    }
}

int main()
{
    char str[35];
    freopen("poj2418.txt","r",stdin);
    freopen("poj2418ans.txt","w",stdout);
    index=1;
    n=len=0;
    while (gets(str))
    {
        Insert(str);
        n++;
    }
    PreOrder(1);
    return 0;
}
