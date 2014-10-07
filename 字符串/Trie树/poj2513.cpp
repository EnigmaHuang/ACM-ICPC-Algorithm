#include<stdio.h>
#include<string.h>

#define CharsetSize 26       //字符集大小
#define CharsetBase 'a'     //字符集最小字符

#define MaxN 500001

struct TrieNode
{
    int id;
    TrieNode *next[26];
};

TrieNode *root,mem[5100050];
int index;

TrieNode *Create()
{
    TrieNode *p=&mem[index++];
    int i;
    for (i=0;i<CharsetSize;i++) p->next[i]=NULL;
    return p;
};

void Insert(char *str, int wid)
{
    TrieNode *p=root;
    int i,k;
    for (i=0;str[i];i++)
    {
        k=str[i]-CharsetBase;
        if (p->next[k]==NULL) p->next[k]=Create();
        p=p->next[k];
    }
    p->id=wid;
}

int Search(char *str)
{
    TrieNode *p=root;
    int i,k;
    for (i=0;str[i];i++)
    {
        k=str[i]-CharsetBase;
        if (p->next[k]==NULL) return 0;
        p=p->next[k];
    }
    return p->id;
}

int fa[MaxN],deg[MaxN],cnt;

int Find(int x)
{
    if (x!=fa[x]) fa[x]=Find(fa[x]);
    return fa[x];
}

int Judge()    //判断是否满足欧拉路
{
    int i,k,odd=0;
    for (i=1;i<=cnt;i++) if (deg[i]%2==1) odd++;
    if (odd!=0 && odd!=2) return 0;
    k=Find(1);
    for (i=2;i<=cnt;i++) if (k!=Find(i)) return 0;
    return 1;
}

int main()
{
    int id,x,y,findx,findy,i;
    char s[15],e[15];
    freopen("poj2513.txt","r",stdin);
    freopen("poj2513ans.txt","w",stdout);
    for (i=0;i<MaxN;i++) fa[i]=i;
    memset(deg,0,sizeof(deg));
    index=cnt=0;
    root=Create();
    while (scanf("%s %s",s,e)!=EOF)
    {
    	x=Search(s);
    	y=Search(e);
    	if (x==0)
    	{
	    Insert(s,++cnt);
	    x=cnt;
    	}
    	if (y==0)
    	{
	    Insert(e,++cnt);
	    y=cnt;
    	}
    	deg[x]++;
    	deg[y]++;
	findx=Find(x);
	findy=Find(y);
	if (findx!=findy) fa[findx]=findy;
    }
    if (Judge()) printf("Possible\n"); else printf("Impossible\n");
    return 0;
}
