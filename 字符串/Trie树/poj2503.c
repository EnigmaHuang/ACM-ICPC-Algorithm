#include<stdio.h>
#include<string.h>

#define CharsetSize 26      //字符集大小
#define CharsetBase 'a'     //字符集最小字符

#define MaxN 100001

struct TrieNode
{
    char word[11];
    int next[CharsetSize];
}trie[MaxN*11];

int index;

void Insert(char str[],char eword[])
{
    int i,p=0;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)
	    trie[p].next[str[i]-CharsetBase]=++index;
        p=trie[p].next[str[i]-CharsetBase];
    }
    strcpy(trie[p].word,eword);
}

void Output (char str[])
{
    int p=0,i;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)
        {
            printf("eh\n");
            return;
        }
	p=trie[p].next[str[i]-CharsetBase];
    }
    printf("%s\n",trie[p].word);
}

int main()
{
    int i;
    char tmp[30],str1[15],str2[15];
    freopen("poj2503.txt","r",stdin);
    freopen("poj2503ans.txt","w",stdout);
    for (i=0;i<26;i++) trie[0].next[i]=0;
    index=1;
    while (gets(tmp))
    {
	if (tmp[0]==0) break;
	sscanf(tmp,"%s%s",str1,str2); //从字符串中读入
	Insert(str2,str1);
    }
    while (scanf("%s",tmp)!=EOF) Output(tmp);
    return 0;
}
