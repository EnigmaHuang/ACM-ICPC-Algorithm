#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN     1005

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

char s1[MaxN],s2[MaxN],s12[MaxN],dst[MaxN];

int main()
{
    int n,c,i,t,cases,ans,tmp,id;
    freopen("poj3087.txt","r",stdin);
    freopen("poj3087ans.txt","w",stdout);
    scanf("%d",&cases);
    for (t=1;t<=cases;t++)
    {
        scanf("%d",&c);
        n=c*2;
        scanf("%s%s%s",s1,s2,dst);
        InitHash();
        ans=0;
        printf("%d ",t);
        while (1)
        {
            ans++;
            for (i=0;i<n;i+=2) s12[i]=s2[i/2];
            for (i=1;i<n;i+=2) s12[i]=s1[i/2];
            s12[n]='\0';
            if (strcmp(dst,s12)==0)
            {
                printf("%d\n",ans);
                break;
            }
            else
            {
                tmp=memtop-mem;
                id=Find(s12,INSERT);
                if (id!=memtop-mem-1) /*不是新增的*/
                {
                    printf("-1\n");
                    break;
                }
            }
            for (i=0;i<c;i++) s1[i]=s12[i];
            for (i=0;i<c;i++) s2[i]=s12[i+c];
        }
    }
    return 0;
}
