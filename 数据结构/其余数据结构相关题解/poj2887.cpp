#include<stdio.h>
#include<string.h>

/*----------块状链表模板----------
初始时置root=NULL，用完以后需要destory(root)
*/


#define MaxN 1000001
#define MaxM 1105     //MaxM为sqrt(MaxN)级别的大小
#define KeyT char     //KeyT为存储的信息类型

struct TData
{
    int s;
    KeyT a[2*MaxM+5];
    TData *next;
};

typedef struct TData* PData;

PData root;

void Locate(PData &k,int &pos)
{
    k=root;
    while (pos>k->s && k->next!=NULL)
    {
        pos-=k->s;
        k=k->next;
    }
}

void Init(KeyT *data,int size)
{
    int i,j;
    PData k,t;
    root=new(TData);
    k=root;
    i=0;
    while (i<size)
    {
        for (j=1;j<=MaxM && i<size;j++,i++) k->a[j]=data[i];
        j--;
        k->s=j;
        k->next=NULL;
        if (j==MaxM)
        {
            t=new(TData);
            k->next=t;
            t->s=0;
            k=t;
        }
        if (i==size) return;
    }
}

void Insert(KeyT x,int pos)
{
    PData k,t;
    if (root==NULL)
    {
        root=new(TData);
        root->s=1;
        root->a[1]=x;
        return;
    }
    Locate(k,pos);
    memmove(k->a+pos+1,k->a+pos,sizeof(KeyT)*(k->s-pos+1));
    k->s++;
    k->a[pos]=x;
    if (k->s==2*MaxM)
    {
        t=new(TData);
        t->next=k->next;
        k->next=t;
        memcpy(t->a+1,k->a+MaxM+1,sizeof(KeyT)*MaxM);
        t->s=k->s=MaxM;
    }
}

void Delete(int pos)
{
    PData k;
    Locate(k,pos);
    memmove(k->a+pos,k->a+pos+1,sizeof(KeyT)*(k->s-pos));
    k->s--;
}

KeyT Find(int pos)
{
    PData k;
    Locate(k,pos);
    return k->a[pos];
}

void Modify(int pos,KeyT newval)
{
    PData k;
    Locate(k,pos);
    k->a[pos]=newval;
}

void Clean(PData k)
{
    if (k->next!=NULL) Clean(k->next);
    delete(k);
}

/*----------块状链表模板----------*/


char start[MaxN];

int main()
{
    int q,i,pos,n;
    char cmd,c;
    freopen("poj2887.txt","r",stdin);
    freopen("poj2887ans.txt","w",stdout);
    scanf("%s",start);
    root=NULL;
    n=strlen(start);
    Init(start,n);
    scanf("%d\n",&q);
    while (q--)
    {
        scanf("%c ",&cmd);
        if (cmd=='Q')
        {
            scanf("%d\n",&pos);
            printf("%c\n",Find(pos));
        }
        else
        {
            scanf("%c %d\n",&c,&pos);
            if (pos>n+1) pos=n+1;
            Insert(c,pos);
            n++;
        }
    }
    return 0;
}
