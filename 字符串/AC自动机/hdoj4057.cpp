#include<stdio.h>
#include<string.h>

#define MaxN 1001
#define CharsetSize 4
#define Max(a,b) (a)>(b)?(a):(b)

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
    if (c=='A') return 0;
    if (c=='C') return 1;
    if (c=='T') return 2;
    if (c=='G') return 3;
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

int n,m,val[11],ans;
int dp[2][MaxN][1024];

int GetKindVal(int x)
{
    int res=0,i;
    for (i=0;i<m;i++) if (x&(1<<i)) res+=val[i];
    return res;
}

void DP()
{
    int i,j,k,maxid,tmp,pos,jj,kk;

    maxid=1<<m;
    memset(dp,0,sizeof(dp));

    dp[0][0][0]=1;
    //采取滚动数组，i&1为当前i更新的状态，(i+1)&1为i-1的状态
    for (i=1;i<=n;i++)
    {
        memset(dp[i&1],0,sizeof(dp[i&1]));
        for (j=0;j<memtop;j++)
            for (k=0;k<maxid;k++)
		if (dp[(i+1)&1][j][k])
		{
                    for (pos=0;pos<CharsetSize;pos++)
                    {
                        jj=mem[j].next[pos]-root;
                        kk=mem[j].next[pos]->flag;
                        dp[i&1][jj][kk|k]=1;
                    }
                }
    }
    
    ans=-0x3f3f3f3f;
    for (j=0;j<memtop;j++)
        for (k=0;k<maxid;k++) if (dp[n&1][j][k])
        {
            tmp=GetKindVal(k);
            ans=Max(ans,tmp);
        }
}

int main()
{
    int i;
    char word[15];
    freopen("hdoj4057.txt","r",stdin);
    freopen("hdoj4057ans.txt","w",stdout);
    while (scanf("%d%d",&m,&n)!=EOF)
    {
        InitACMem();
        for (i=0;i<m;i++)
        {
            scanf("%s%d",word,&val[i]);
            Insert(word,i);
        }
        BuildAC();
        DP();
        if (ans<0) printf("No Rabbit after 2012!\n");
        else printf("%d\n",ans);
    }
    return 0;
}
