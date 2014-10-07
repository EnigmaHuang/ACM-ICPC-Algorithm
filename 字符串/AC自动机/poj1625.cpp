#include<stdio.h>
#include<string.h>

#define MaxN 805
#define CharsetSize 50

using namespace std;

int Alphabet[256+128],CurCharsetSize;

struct TTrieNode
{
    int flag;
    TTrieNode *next[CharsetSize];
    TTrieNode *fail;
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
    return Alphabet[c+128];
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
        for (i=0;i<CurCharsetSize;i++)
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

struct BigInt
{
    const static int mod=10000;
    int data[50],len;
    BigInt()
    {
        memset(data,0,sizeof(data));
        len=1;
    }
    BigInt operator + (const BigInt &b) const
    {
        BigInt res;
        int i;
        res.len=len>b.len?len:b.len;
        memset(res.data,0,sizeof(res.data));
        for (i=0;i<res.len;i++)
        {
            res.data[i]+=(i<len?data[i]:0)+(i<b.len?b.data[i]:0);
            res.data[i+1]+=res.data[i]/mod;
            res.data[i]%=mod;
        }
        if (res.data[res.len]>0) res.len++;
        return res;
    }
    void Clear()
    {
        memset(data,0,sizeof(data));
        len=1;
    }
    void Print()
    {
        int i;
        printf("%d",data[len-1]);
        for (i=len-2;i>=0;i--) printf("%04d",data[i]);
    }
};

BigInt dp[51][MaxN],ans;

int n,m,p;

void DP()
{
    int i,j,k,pos;
    
    for (i=0;i<=m;i++)
        for (j=0;j<p;j++) dp[i][j].Clear();

    dp[0][0].data[0]=1;
    
    for (i=1;i<=m;i++)
        for (j=0;j<memtop;j++) if (!mem[j].flag)
        {
            for (k=0;k<n;k++)
            {
                    pos=mem[j].next[k]-root;
                    if (!mem[pos].flag) dp[i][pos]=dp[i][pos]+dp[i-1][j];
            }
        }

    ans.Clear();
    for (i=0;i<memtop;i++) ans=ans+dp[m][i];
}

int main()
{
    int i,len;
    char word[50],alphabet[50];
    freopen("poj1625.txt","r",stdin);
    freopen("poj1625ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&m,&p)!=EOF)
    {
        CurCharsetSize=n;

        /*建立新的字母表映射*/
        scanf("%s",alphabet);
        memset(Alphabet,0,sizeof(Alphabet));
        len=strlen(alphabet);
        //char 的整数范围是-127~127，所以要加128
        for (i=0;i<len;i++) Alphabet[alphabet[i]+128]=i;

        /*建Trie树*/
        InitACMem();
        for (i=0;i<p;i++)
        {
            scanf("%s",word);
            Insert(word);
        }
        BuildAC();

        DP();
        ans.Print();
        printf("\n");
    }
}
