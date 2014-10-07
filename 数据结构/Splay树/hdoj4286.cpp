/*
这题巨坑爹：
1、要用C++交，G++会堆栈溢出，因为Splay树可能退化，
   退化会造成堆栈很深，而且还要加编译指令。
2、管好内存！
*/

#include<stdio.h>
#include<string.h>

#define Min(a,b) (a)<(b)?(a):(b)
#define inf  0x3f3f3f3f
#define MaxN 1000050
#pragma comment(linker, "/STACK:1024000000,1024000000")

int n,m,posr,posl;

/*----------Splay Template Start----------*/

typedef struct SplayNode* Node;

struct SplayNode
{
    Node pre,ch[2];
    int value/*,lazy,min*/;   //结点键值，lazy标记，子树最小值
    int size,rev;         //子树大小，翻转标记
    void init(int _value)
    {
        pre=ch[0]=ch[1]=NULL;
        /*min=*/value=_value;
        //lazy=0;
        size=1;
        rev=0;
    }
}mem[MaxN];      //内存池
int memtop;      //内存池已分配到的最大位置

/*
Node stack[MaxN]; //内存池回收栈
int stacktop;     //栈顶指针
*/

Node root;

inline int GetSize(Node &x)  //取得x子树大小，主要是解决x=NULL的情况
{
    return x?x->size:0;
}

void PushDown(Node &x)  //将x标记下移
{
    if (!x) return;
    /*if (x->lazy)
    {
        int w=x->lazy;
        x->value+=w;
        if (x->ch[0])
        {
            x->ch[0]->lazy+=w;
            x->ch[0]->min+=w;
        }
        if (x->ch[1])
        {
            x->ch[1]->lazy+=w;
            x->ch[1]->min+=w;
        }
        x->lazy=0;
    }*/
    if (x->rev)
    {
        Node t=x->ch[0];
        x->ch[0]=x->ch[1];
        x->ch[1]=t;
        x->rev=0;
        if (x->ch[0]) x->ch[0]->rev^=1;
        if (x->ch[1]) x->ch[1]->rev^=1;
    }
}

void Update(Node &x)  //更新x结点信息
{
    if (!x) return;
    x->size=1;
    //x->min=x->value;
    if (x->ch[0])
    {
        //x->min=Min(x->min,x->ch[0]->min);
        x->size+=x->ch[0]->size;
    }
    if (x->ch[1])
    {
        //x->min=Min(x->min,x->ch[1]->min);
        x->size+=x->ch[1]->size;
    }
}

void Rotate(Node &x,int d) //旋转操作，d=0表示左旋，d=1表示右旋
{
    Node y=x->pre;
    PushDown(y);
    PushDown(x);
    PushDown(x->ch[d]);
    y->ch[!d]=x->ch[d];
    if (x->ch[d]!=NULL) x->ch[d]->pre=y;
    x->pre=y->pre;
    if (y->pre!=NULL)
    {
        if (y->pre->ch[0]==y) y->pre->ch[0]=x;
        else y->pre->ch[1]=x;
    }
    x->ch[d]=y;
    y->pre=x;
    Update(y);
    if (y==root) root=x;//因为是指针，所以root可能被转下去了
}

void Splay(Node &src,Node &dst) // Splay操作，把结点src转到结点dst的子节点
{
    PushDown(src);
    while (src!=dst)
    {
        if (src->pre==dst)
        {
            if (dst->ch[0]==src) Rotate(src,1);
            else Rotate(src,0);
            break;
        }
        else
        {
            Node y=src->pre,z=y->pre;
            if (z->ch[0]==y)
        {
                if (y->ch[0]==src)
                {
                    Rotate(y,1);
            Rotate(src,1); //一字形旋转
            }
                else
                {
            Rotate(src,0);
            Rotate(src,1); //之字形旋转
            }
        }
            else
            {
            if (y->ch[1]==src)
                {
                    Rotate(y,0);
            Rotate(src,0);  //一字形旋转
            }
                else
                {
            Rotate(src,1);
            Rotate(src,0); // 之字形旋转
            }
        }
            if (z==dst) break;//转了之后，x就到了原来z的位置，如果z就是要到的地方，就可以退出了
        }
        Update(src);
    }
    Update(src);
}

void Select(int k,Node &f)  //把第k个元素调到f的子节点
{
    int tmp;
    Node t;
    t=root;
    while (1)
    {
        PushDown(t);
        tmp=GetSize(t->ch[0]);  //得到t左子树的大小
        if (k==tmp+1) break;    //得出t即为查找结点，退出
        if (k<=tmp) t=t->ch[0]; //第k个结点在t左边，向左走
        else //否则在右边，而且在右子树中，这个结点不再是第k个
        {
        k-=tmp+1;
        t=t->ch[1];
        }
    }
    PushDown(t);
    Splay(t,f);   //执行旋转
}

inline void SelectOperateSegment(int l,int r)   //选择操作的区间
{
    Select(l,root);
    Select(r+2,root->ch[1]);
}

void Insert(int pos,int value)   //在pos位置后面插入一个新值value
{
    Select(pos+1,root);
    Select(pos+2,root->ch[1]);
    //SelectOperateSegment(pos+1,pos);
    //这种写法有点意义不明，不使用

    Node t;
    Node x=root->ch[1];

    PushDown(root);
    PushDown(x);

    /*if (stacktop>0)
    {
        t=stack[stacktop];
        stacktop--;
    }
    else*/
    {
        t=&mem[memtop];
        memtop++;
    }
    t->init(value);
    t->ch[1]=x;
    x->pre=t;
    root->ch[1]=t;
    t->pre=root;
    Splay(x,root);
}

void Add(int a,int b,int value)  //区间[a,b]中的数都加上value
{
    SelectOperateSegment(a,b);
    Node x=root->ch[1]->ch[0];
    PushDown(x);
    Update(x);
    //x->min+=value;
    //x->lazy+=value;
    Splay(x,root);
}

void Reverse(int a,int b)        //区间[a,b]中的数翻转
{
    SelectOperateSegment(a,b);
    root->ch[1]->ch[0]->rev^=1;
    Node x=root->ch[1]->ch[0];
    Splay(x,root);
}

void Erase(int pos)              //抹去第pos个元素
{
    SelectOperateSegment(pos,pos);
    PushDown(root->ch[1]);
    //stack[++stacktop]=root->ch[1]->ch[0];  //回收内存
    root->ch[1]->ch[0]=NULL;
    Node x=root->ch[1];
    Splay(x,root);
}

void InOrderTraversal(Node x)
{
    if (!x) return;
    PushDown(x);
    InOrderTraversal(x->ch[0]);
    if (x->value!=inf)
    {
        printf("%d",x->value);
        n--;
        if (n) printf(" ");
    }
    InOrderTraversal(x->ch[1]);
}

void InitSplayTree()
{
    int i;
    memtop=0;
    root=&mem[memtop];
    memtop++;
    root->init(inf);
    root->ch[1]=&mem[memtop];
    memtop++;
    root->ch[1]->init(inf);
}

/*----------Splay Template Over----------*/

int main()
{
    int i,t,val;
    char cmd[255];
    freopen("hdoj4286.txt","r",stdin);
    freopen("hdoj4286ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        InitSplayTree();
        for (i=0;i<n;i++)
        {
            scanf("%d",&val);
            Insert(i,val);
        }

        scanf("%d%d",&posl,&posr);
        posl--;

        scanf("%d\n",&m);
        for (i=0;i<m;i++)
        {
            scanf("%s",cmd);
            if (strcmp(cmd,"MoveLeft")==0)
            {
                scanf("%s",cmd);
                if (cmd[0]=='R') posr--;
                if (cmd[0]=='L') posl--;
                if (posl<0) posl=0;
                if (posr<0) posr=0;
                scanf("\n");
            }
            if (strcmp(cmd,"MoveRight")==0)
            {
                scanf("%s",cmd);
                if (cmd[0]=='R') posr++;
                if (cmd[0]=='L') posl++;
                if (posr>n) posr=n;
                if (posl>n) posl=n;
                scanf("\n");
            }
            if (strcmp(cmd,"Insert")==0)
            {
                scanf("%s %d\n",cmd,&val);
                if (cmd[0]=='L') Insert(posl,val);
                if (cmd[0]=='R') Insert(posr,val);
                posr++;
                n++;
            }
            if (strcmp(cmd,"Delete")==0)
            {
                scanf("%s",cmd);
                scanf("\n");
                if (n==0) continue;
                if (cmd[0]=='L') Erase(posl+1);
                if (cmd[0]=='R') Erase(posr);
                posr--;
                n--;
            }
            if (strcmp(cmd,"Reverse")==0)
            {
                Reverse(posl+1,posr);
                scanf("\n");
            }
        }
        InOrderTraversal(root);
        printf("\n");
    }
    return 0;
}
