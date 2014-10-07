#include<stdio.h>
#include<string.h>

#define CharsetSize 4       //字符集大小

#define MaxN 102
#define MOD 100000

using namespace std;

struct TTrieNode
{
    int flag;
    int next[CharsetSize];
    int fail;
}mem[MaxN];

int root,q[MaxN];

int memtop;

int NewNode()
{
    mem[memtop].flag=0;
    mem[memtop].fail=-1;
    memset(mem[memtop].next,0,sizeof(mem[memtop].next));
    memtop++;
    return memtop-1;
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
    int i,len,pos,p=root;
    len=strlen(str);
    for (i=0;i<len;i++)
    {
        pos=CharPos(str[i]);
        if (mem[p].next[pos]==0) mem[p].next[pos]=NewNode();
        p=mem[p].next[pos];
    }
    mem[p].flag=1;
}

void BuildAC()  //BFS初始化fail指针
{
    int p,pos;
    int i,head,tail;
    head=tail=0;
    q[tail++]=root;
    while (head!=tail)
    {
        p=q[head++];
        pos=0;
        for (i=0;i<CharsetSize;i++)
        {
            if (mem[p].next[i]!=0)
            {
                if (p==root) mem[mem[p].next[i]].fail=root;  //root的失败指针指向root
                else
                {
                    pos=mem[p].fail;       //失败指针
                    while (pos!=-1)  //两种情况结束：匹配为空 or 找到匹配
                    {
                        if (mem[p].next[i]!=0) //找到匹配
                        {
                             mem[mem[p].next[i]].fail=mem[pos].next[i];
                             mem[mem[p].next[i]].flag|=mem[mem[pos].next[i]].flag;
                             break;
                        }
                        pos=mem[pos].fail;
                    }
                    //为空，从头匹配
                    if (pos==-1) mem[mem[p].next[i]].fail=root;
                }
                q[tail++]=mem[p].next[i];
            }
            else
            {
                if (p==root) mem[p].next[i]=root;
                else mem[p].next[i]=mem[mem[p].fail].next[i];
            }
        }
    }
}

struct Matrix
{
    long long v[MaxN][MaxN];
    Matrix()
    {
        memset(v,0,sizeof(v));
    }
    Matrix operator * (const Matrix &B)
    {
        int i,j,k;
        Matrix C;
        for (i=0;i<memtop;i++)
            for (j=0;j<memtop;j++)
                for (k=0;k<memtop;k++)
                    C.v[i][j]=(C.v[i][j]+v[i][k]*B.v[k][j])%MOD;
        return C;
    }
};

Matrix Pow(Matrix A,int exp)
{
    int i;
    Matrix B;
    memset(B.v,0,sizeof(B.v));
    for (i=0;i<memtop;i++) B.v[i][i]=1;
    while (exp)
    {
        if (exp&1) B=B*A;
        A=A*A;
        exp>>=1;
    }
    return B;
}

int n,m;
Matrix Trie,res;

void TrieToMatrix()
{
    int i,j,pos;
    memset(Trie.v,0,sizeof(Trie.v));
    for (i=0;i<memtop;i++) if (mem[i].flag!=1)
    {
        for (j=0;j<CharsetSize;j++)
        {
            pos=mem[i].next[j];
            if (mem[pos].flag) continue;
            Trie.v[i][pos]++;
        }
    }
}

int main()
{
    int i;
    char word[20];
    long long ans;
    freopen("poj2778.txt","r",stdin);
    freopen("poj2778ans.txt","w",stdout);
    while (scanf("%d%d",&m,&n)!=EOF)
    {
        InitACMem();
        while (m--)
        {
            scanf("%s",word);
            Insert(word);
        }
        BuildAC();
        TrieToMatrix();
        res=Pow(Trie,n);
        ans=0;
        for (i=0;i<memtop;i++) ans=(ans+res.v[0][i])%MOD;
        printf("%lld\n",ans%MOD);
    }
    return 0;
}
