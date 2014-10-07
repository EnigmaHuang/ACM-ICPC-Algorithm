#include<stdio.h>
#include<string.h>

#define CharsetSize 4       //字符集大小

#define MaxN 1005

using namespace std;

struct TTrieNode
{
    int flag;
    TTrieNode *next[CharsetSize];
    TTrieNode *fail;
    TTrieNode()
    {
        fail=NULL;
        flag=0;
        memset(next,NULL,sizeof(next));
    }
}mem[MaxN];

typedef struct TTrieNode* PTrieNode;

PTrieNode root,q[MaxN];

int memtop;

/*
手动内存池分配，注意内存池大小
由于使用new的方式在新的一组数据里没有执行
回收操作，有内存泄露超过内存峰值的隐患，
所以加上了手动内存分配。
*/
PTrieNode NewNode()
{
    mem[memtop].flag=0;
    mem[memtop].fail=NULL;
    memset(mem[memtop].next,NULL,sizeof(mem[memtop].next));
    memtop++;
    return &mem[memtop-1];
}

void InitACMem()
{
    memtop=0;
    memset(mem,0,sizeof(mem));
    root=NewNode();
}

int CharPos(char c)
{
    if (c=='A') return 0;
    if (c=='C') return 1;
    if (c=='T') return 2;
    if (c=='G') return 3;
}

void Insert(char *str)
{
    int i,len,pos;
    PTrieNode p=root;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        pos=CharPos(str[i]);
        if (p->next[pos]==NULL) p->next[pos]=NewNode();//new TTrieNode();
        p=p->next[pos];
    }
    p->flag=1;
}

void BuildAC()  //BFS初始化fail指针
{
    PTrieNode p,pos;
    int i,head,tail;
    head=tail=0;
    q[tail++]=root;
    while (head!=tail)
    {
        p=q[head++];
        pos=NULL;
        for (i=0;i<CharsetSize;i++)
        {
            if (p->next[i]!=NULL)
            {
                if (p==root) p->next[i]->fail=root;  //root的失败指针指向root
                else
                {
                    pos=p->fail;       //失败指针
                    while (pos!=NULL)  //两种情况结束：匹配为空 or 找到匹配
                    {
                        if (pos->next[i]!=NULL) //找到匹配
                        {
                             p->next[i]->fail=pos->next[i];
                             p->next[i]->flag|=pos->next[i]->flag;
                             break;
                        }
                        pos=pos->fail;
                    }
                    //为空，从头匹配
                    if (pos==NULL) p->next[i]->fail=root;
                }
                q[tail++]=p->next[i];
            }
            else
            {
                if (p==root) p->next[i]=root;
                else p->next[i]=p->fail->next[i];
            }
        }
    }
}

char DNA[MaxN];
int dp[MaxN][MaxN];

int main()
{
    int n,t=0,i,j,DNALen,pos,tmp,ans;
    char word[255];
    PTrieNode p;
    freopen("poj3691.txt","r",stdin);
    freopen("poj3691ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        InitACMem();
        for (i=0;i<n;i++)
        {
            scanf("%s",word);
            Insert(word);
        }
        BuildAC();
        scanf("%s",DNA);
        DNALen=strlen(DNA);
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;
        for (i=1;i<=DNALen;i++)
            for (j=0;j<memtop;j++)
            {
                if (dp[i-1][j]==-1) continue;
                for (pos=0;pos<CharsetSize;pos++)
                {
                    p=mem[j].next[pos];
                    if (p->flag) continue;
                    tmp=dp[i-1][j]+(pos!=CharPos(DNA[i-1]));
                    if (dp[i][p-root]==-1 || dp[i][p-root]>tmp) dp[i][p-root]=tmp;
                }
            }
        ans=-1;
        for (i=0;i<memtop;i++) if (dp[DNALen][i]!=-1 && (ans==-1 || dp[DNALen][i]<ans)) ans=dp[DNALen][i];
        printf("Case %d: %d\n",++t,ans);
    }
    return 0;
}
