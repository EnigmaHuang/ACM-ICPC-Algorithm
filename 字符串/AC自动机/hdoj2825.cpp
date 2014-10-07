#include<stdio.h>
#include<string.h>

#define MaxN 105
#define CharsetSize 26
#define CharsetBase 'a'
#define MOD 20090717

using namespace std;

struct TTrieNode
{
    int flag;
    TTrieNode *next[CharsetSize];
    TTrieNode *fail;
}mem[MaxN];

typedef struct TTrieNode* PTrieNode;

PTrieNode root,q[MaxN];

int memtop;

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
    return c-'a';
}

void Insert(char *str,int id)
{
    int i,len,pos;
    PTrieNode p=root;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        pos=CharPos(str[i]);
        if (p->next[pos]==NULL) p->next[pos]=NewNode();
        p=p->next[pos];
    }
    p->flag|=(1<<id);
}

void BuildAC()  //BFS初始化fail指针
{
    PTrieNode p,pos;
    int i,head,tail;
    head=tail=0;
    q[tail++]=root;
    root->fail=root;
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

int GetKindNum(int x)
{
    int res=0;
    while (x)
    {
        if (x&1) res++;
        x>>=1;
    }
    return res;
}

int n,m,p,ans;
int dp[26][MaxN][1024];

void DP()
{
    int i,j,k,maxid,tmp,pos,jj,kk;
    
    maxid=1<<m;

    //不知为何写for会比memset快一点
    for (i=0;i<=n;i++)
        for (j=0;j<memtop;j++)
            for (k=0;k<maxid;k++) dp[i][j][k]=0;
    
    dp[0][0][0]=1;
    for (i=1;i<=n;i++)
        for (j=0;j<memtop;j++)
            for (k=0;k<maxid;k++)
            {
                if (dp[i-1][j][k]==0) continue;
                tmp=dp[i-1][j][k];
                for (pos=0;pos<CharsetSize;pos++)
                {
                    jj=mem[j].next[pos]-root;
                    kk=mem[j].next[pos]->flag;
                    dp[i][jj][kk|k]=(tmp+dp[i][jj][kk|k])%MOD;
                }
            }

    ans=0;
    for (j=0;j<memtop;j++)
        for (k=0;k<maxid;k++)
            if (GetKindNum(k)>=p) ans=(ans+dp[n][j][k])%MOD;
}

int main()
{
    int i;
    char word[15];
    freopen("hdoj2825.txt","r",stdin);
    freopen("hdoj2825ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&m,&p)!=EOF)
    {
        if (n==0 && m==0 && p==0) break;
        InitACMem();
        for (i=0;i<m;i++)
        {
            scanf("%s",word);
            Insert(word,i);
        }
        BuildAC();
        DP();
        printf("%d\n",ans);
    }
    return 0;
}
