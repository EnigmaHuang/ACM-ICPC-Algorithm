#include<stdio.h>
#include<string.h>

#define MaxN 10005

struct TDictRec
{
    char word[16];
    int id,len,weight;
}dict[MaxN];

int n,startpos[16];

/*----------BKDR Hash Table Template----------*/
#define MOD      100007
#define BKDRSeed 131
#define INSERT   0
#define QUERY    1

struct TNode
{
    struct TNode* next;
    char s[16];
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

void QSort(int l,int r)
{
    int i=l,j=r,mid;
    struct TDictRec swap;
    mid=dict[(l+r)/2].weight;
    while (i<=j)
    {
        while (dict[i].weight<mid) i++;
        while (mid<dict[j].weight) j--;
        if (i<=j)
        {
            swap=dict[i];
            dict[i]=dict[j];
            dict[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int Dist(char* a,char *b)
{
    int i,j,len1,len2,res=0;
    len1=strlen(a);
    len2=strlen(b);
    if (len1<len2)
    {
        i=0;j=0;
        while (i<len1 && j<len2)
        {
            if (a[i]==b[j])
            {
                i++;
                j++;
            }
            else
            {
                res++;
                j++;
            }
        }
        res+=len1-i+len2-j;
    }
    else if (len1==len2)
    {
        for (i=0;i<len1;i++) if (a[i]!=b[i]) res++;
    }
    else res=Dist(b,a);
    return res;
}

struct TDictRec ans[MaxN];
int cnt;

void QSort2(int l,int r)
{
    int i=l,j=r,mid;
    struct TDictRec swap;
    mid=ans[(l+r)/2].id;
    while (i<=j)
    {
        while (ans[i].id<mid) i++;
        while (mid<ans[j].id) j--;
        if (i<=j)
        {
            swap=ans[i];
            ans[i]=ans[j];
            ans[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort2(i,r);
    if (l<j) QSort2(l,j);
}

void CheckLen(char* word,int len)
{
    int i;
    
    for (i=startpos[len];dict[i].len==len;i++)
        if (Dist(word,dict[i].word)==1) ans[cnt++]=dict[i];
}

int main()
{
    char word[20];
    int i,k,nowlen;
    freopen("poj1035.txt","r",stdin);
    freopen("poj1035ans.txt","w",stdout);

    InitHash();

    n=0;
    while (scanf("%s",word) && word[0]!='#')
    {
        strcpy(dict[n].word,word);
        dict[n].id=n;
        dict[n].len=strlen(word);
        dict[n].weight=dict[n].len*100000+n;
        n++;
        Find(word,INSERT);
    }

    QSort(0,n-1);

    nowlen=0;
    memset(startpos,-1,sizeof(startpos));
    for (i=0;i<n;i++)
    {
        if (dict[i].len==nowlen) continue;
        else
        {
            nowlen=dict[i].len;
            startpos[nowlen]=i;
        }
    }
    
    while (scanf("%s",word) && word[0]!='#')
    {
        nowlen=strlen(word);
        cnt=0;
        if (Find(word,QUERY)!=-1) printf("%s is correct\n",word);
        else
        {
            printf("%s:",word);
            CheckLen(word,nowlen);
            if (nowlen==1) CheckLen(word,2);
            else if (nowlen==15) CheckLen(word,14);
            else
            {
                CheckLen(word,nowlen-1);
                CheckLen(word,nowlen+1);
            }
            QSort2(0,cnt-1);
            for (i=0;i<cnt;i++) printf(" %s",ans[i].word);
            printf("\n");
        }
    }
    
    return 0;
}
