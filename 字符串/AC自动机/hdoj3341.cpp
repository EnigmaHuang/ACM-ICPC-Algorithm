#include<stdio.h>
#include<string.h>

#define MaxN 501
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

void Insert(char *str)
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
    p->flag++;
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
                             p->next[i]->flag+=pos->next[i]->flag;
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

int n,m,num[4],ans,base[4],DNA[4];
int dp[15001][MaxN];

void GetDNANum(int i)
{
    DNA[0]=i/base[0];
    DNA[1]=(i%base[0])/base[1];
    DNA[2]=(i%base[1])/base[2];
    DNA[3]=i%base[2];
}

void Solve()
{
    int i,j,k,t;
    PTrieNode p;

    base[3]=1;
    for (i=2;i>=0;i--) base[i]=base[i+1]*(num[i+1]+1);

    t=0;
    for (i=0;i<4;i++) t+=base[i]*num[i];
    
    memset(dp,-1,sizeof(dp));
    dp[0][0]=0;
    ans=0;
    
    for (i=0;i<=t;i++)
    {
	GetDNANum(i);
	if (DNA[0]>num[0] || DNA[1]>num[1]
	 || DNA[2]>num[2] || DNA[3]>num[3]) continue;
	for (j=0;j<memtop;j++) if (dp[i][j]!=-1)
	{
	    for (k=0;k<CharsetSize;k++) if (DNA[k]<num[k])
	    {
		p=mem[j].next[k];
		if (dp[i+base[k]][p-root]<dp[i][j]+p->flag)
		    dp[i+base[k]][p-root]=dp[i][j]+p->flag;
	    }
	}
    }
    
    for (i=0;i<memtop;i++) ans=Max(ans,dp[t][i]);
}

char str[50];

int main()
{
    int i,t=0;
    char word[15];
    freopen("hdoj3341.txt","r",stdin);
    freopen("hdoj3341ans.txt","w",stdout);
    while (scanf("%d",&m)!=EOF && m)
    {
        InitACMem();
        for (i=0;i<m;i++)
        {
            scanf("%s",word);
            Insert(word);
        }
        BuildAC();
        
        scanf("%s",str);
        n=strlen(str);
        num[0]=num[1]=num[2]=num[3]=0;
        for (i=0;str[i];i++) num[CharPos(str[i])]++;
        
        Solve();
        printf("Case %d: %d\n",++t,ans);
    }
    return 0;
}
