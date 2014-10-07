#include<stdio.h>
#include<string.h>

#define CharsetSize 26       //字符集大小
#define CharsetBase 'a'     //字符集最小字符

#define MaxN 500010

using namespace std;

struct TTrieNode
{
    int count;
    TTrieNode *next[CharsetSize];
    TTrieNode *fail;
    TTrieNode()
    {
        fail=NULL;
        count=0;
        memset(next,NULL,sizeof(next));
    }
}mem[240000];

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
    mem[memtop].count=0;
    mem[memtop].fail=NULL;
    memset(mem[memtop].next,NULL,sizeof(mem[memtop].next));
    memtop++;
    return &mem[memtop-1];
}

void Insert(char *str)
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
    p->count++;
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
        pos=str[i]-CharsetBase;
        while (p->next[pos]==NULL && p!=root) p=p->fail;
        p=p->next[pos];
        if (p==NULL) p=root;
        tmp=p;  //tmp用来计算后缀串
        while (tmp!=root && tmp->count!=-1)
        {
            res+=tmp->count;
            tmp->count=-1;    //出现了，只计算一次，不计算次数
            tmp=tmp->fail;
        }
    }
    return res;
}

char str[MaxN*2];

int main()
{
    int t,n,i;
    char word[60];
    freopen("hdoj2222.txt","r",stdin);
    freopen("hdoj2222ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        //root=new TTrieNode();
        memtop=0;
        memset(mem,0,sizeof(mem));
        root=NewNode();
        scanf("%d\n",&n);
        for (i=0;i<n;i++)
        {
            scanf("%s",word);
            Insert(word);
        }
        BuildAC();
        scanf("%s",str);
        printf("%d\n",Query(str));
    }
    return 0;
}
