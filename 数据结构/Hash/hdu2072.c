#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN     1000003

int lastpos;
char s[MaxN];

/*----------BKDR Hash Table Template----------*/
#define MOD      100007
#define BKDRSeed 131
#define INSERT   0
#define QUERY    1

struct TNode
{
    struct TNode* next;
    char s[255];
}mem[MaxN],*hash[MOD],*memtop;
int n;

int BKDRHash(const char* str)
{
    register int hash=0;
    while (*str!=' ' && *str) hash=hash*BKDRSeed+(*str++);
    lastpos=str-s;
    s[lastpos]='\0';
    lastpos++;
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

int main()
{
    int len,ans;
    freopen("hdoj2072.txt","r",stdin);
    freopen("hdoj2072ans.txt","w",stdout);
    while (1)
    {
        gets(s);
        if (s[0]=='#') break;
        InitHash();
        lastpos=0;
        len=strlen(s);
        while (lastpos<len-1)
            Find(&s[lastpos],INSERT);
        ans=memtop-mem;
        strcpy(s," ");
        if (Find(s,QUERY)!=-1) ans--;
        printf("%d\n",ans);
    }
    return 0;
}
