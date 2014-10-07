#include<stdio.h>
#include<string.h>

#define CharsetSize 26       //字符集大小
#define CharsetBase 'A'     //字符集最小字符

#define MaxN 1005

using namespace std;

int ans[MaxN];

struct TTrieNode
{
    int id;
    TTrieNode *next[CharsetSize];
    TTrieNode *fail;
    TTrieNode()
    {
        fail=NULL;
        id=0;
        memset(next,NULL,sizeof(next));
    }
}mem[MaxN*50];

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
    mem[memtop].id=-1;
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


void Insert(char *str,int sid)
{
    int i,len,pos;
    PTrieNode p=root;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        pos=str[i]-CharsetBase;
        if (p->next[pos]==NULL) p->next[pos]=NewNode();//new TTrieNode();
        p=p->next[pos];
    }
    p->id=sid;
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
        for (i=0;i<CharsetSize;i++) if (p->next[i]!=NULL)
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
                         break;
                    }
                    pos=pos->fail;
                }
                //为空，从头匹配
                if (pos==NULL) p->next[i]->fail=root;
            }
            q[tail++]=p->next[i];
        }
    }
}

int Query(char *str)
{
    int i,pos,len,res;
    PTrieNode p=root,tmp;
    res=0;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        if (str[i]<'A' || str[i]>'Z')
        {
            p=root;
            continue;
        }
        pos=str[i]-CharsetBase;
        while (p->next[pos]==NULL && p!=root) p=p->fail;
        p=p->next[pos];
        if (p==NULL) p=root;
        tmp=p;  //tmp用来计算后缀串
        while (tmp!=root)
        {
            if (tmp->id>-1) ans[tmp->id]++;
            tmp=tmp->fail;
        }
    }
    return res;
}

char code[2000050],word[MaxN][55];

int main()
{
    int i,n;
    freopen("hdoj3065.txt","r",stdin);
    freopen("hdoj3065ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitACMem();
        for (i=0;i<n;i++)
        {
            scanf("%s",word[i]);
            Insert(word[i],i);
        }
        BuildAC();
        scanf("%s",code);
        memset(ans,0,sizeof(ans));
        Query(code);
        for (i=0;i<n;i++) if (ans[i]) printf("%s: %d\n",word[i],ans[i]);
    }
    return 0;
}
