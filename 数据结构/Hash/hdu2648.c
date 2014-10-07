#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN     10005

/*----------BKDR Hash Table Template----------*/
#define MOD      14997
#define BKDRSeed 131
#define INSERT   0
#define QUERY    1

struct TNode
{
    struct TNode* next;
    char s[255];
    int val;
}mem[MaxN],*hash[MOD],*memtop;
int n;

int BKDRHash(const char* str)
{
    register int hash=0;
    while (*str) hash=hash*BKDRSeed+(*str++);
    return (hash&0x7fffffff)%MOD;
}

int Find(const char* s,int mode)  /*查询一个字符串的内存池位置，没有则插入*/
{
    int code=BKDRHash(s);
    struct TNode* p=hash[code];
    while (p)
    {
        if (!strcmp(p->s,s)) return p-mem;
        else p=p->next;
    }
    if (mode==INSERT)
    {
        strcpy(memtop->s,s);
        memtop->next=hash[code];   /*头插法*/
        hash[code]=memtop++;
        return memtop-mem-1;
    }
    else if (mode==QUERY) return -1;
}

void InitHash()
{
    memset(hash,0,sizeof(hash));
    memtop=mem;
}
/*----------BKDR Hash Table Template----------*/

int id[MaxN];

int main()
{
    int n,days,i,dprice,nowprice,ans;
    char shop[255];
    freopen("hdoj2648.txt","r",stdin);
    freopen("hdoj2648ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitHash();
        for (i=0;i<n;i++)
        {
            scanf("%s",shop);
            id[i]=Find(shop,INSERT);
            mem[id[i]].val=0;
        }
        scanf("%d",&days);
        while (days--)
        {
            for (i=0;i<n;i++)
            {
                scanf("%d%s",&dprice,shop);
                id[i]=Find(shop,QUERY);
                mem[id[i]].val+=dprice;
                if (strcmp(shop,"memory")==0) nowprice=mem[id[i]].val;
            }
            ans=1;
            for (i=0;i<n;i++)
                if (mem[id[i]].val>nowprice) ans++;
            printf("%d\n",ans);
        }
    }
    return 0;
}
