#include<stdio.h>

#define CharsetSize 26
#define CharsetBase 'A'
#define MaxN 1000001

struct TrieNode
{
    int id;
    int next[CharsetSize];
}trie[MaxN];

int index;

char map[1001][1001];
int ans[1001][3];
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};
int n,m,w;

void Insert (char str[],int wid)
{
    int p=1,i;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)
        {
            trie[p].next[str[i]-CharsetBase]=++index;
            trie[index].id=-1;  //标记还没到结尾
        }
        p=trie[p].next[str[i]-CharsetBase];
    }
    trie[p].id=wid;         //标记为某单词的结尾
}

void Search(int x,int y,int dir)
{
    int p=1,nowx=x,nowy=y;
    while (nowx>=0 && nowx<n && nowy>=0 && nowy<m)
    {
        if (trie[p].next[map[nowx][nowy]-CharsetBase]==0) break;
        else p=trie[p].next[map[nowx][nowy]-CharsetBase];
        if (trie[p].id!=-1)  //走到单词的末尾，记录答案
        {
            ans[trie[p].id][0]=x;
            ans[trie[p].id][1]=y;
            ans[trie[p].id][2]=dir;
        }
        nowx+=dx[dir];
        nowy+=dy[dir];
    }
}

int main ()
{
    int i,j,k;
    char str[1005];
    freopen("poj1204.txt","r",stdin);
    freopen("poj1204ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&m,&w)!=EOF)
    {
        trie[1].id=-1;
        index=1;
        for (i=0;i<n;i++) scanf("%s",map[i]);
        for (i=0;i<w;i++)
        {
            scanf("%s",str);
            Insert(str,i);
        }
        for (i=0;i<n;i++)
            for (j=0;j<n;j++)
                for (k=0;k<8;k++) Search (i,j,k);
	for (i=0;i<w;i++) printf("%d %d %c\n",ans[i][0],ans[i][1],ans[i][2]+CharsetBase);
    }
    return 0;
}
