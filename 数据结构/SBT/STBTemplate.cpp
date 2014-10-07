/*----------Size Balanced Tree Template----------*/

#define KeyType int
#define MaxN 100005

struct SBNode
{
    int     size;
    KeyType key;
    SBNode  *lchild,*rchild;
    SBNode(){}
    SBNode(SBNode *l,SBNode *r,int s,KeyType k):
           lchild(l),rchild(r),size(s),key(k) {}
};

typedef struct SBNode* PSBNode;

class SBTree
{
    private:
        SBNode *root;
        SBNode *_null;
        void LeftRotate (SBNode *&root);
        void RightRotate(SBNode *&root);
        void Maintain(SBNode *&root,bool style);
        void DoInsert(SBNode *&root,KeyType key);
        void DoDelete(SBNode *&root,KeyType key);
        void ClearSubtree(SBNode *root);
        void DoInOrderTraversal(SBNode *root);
    public:
        SBTree();
        ~SBTree();
        void Insert(KeyType key);   //插入元素
        void Delete(KeyType key);   //删除元素
        KeyType GetRank(int k);     //获得第k大元素
        KeyType GetMin();           //获得最小元素
        KeyType GetMax();           //获得最大元素
        void Clear();               //清空
        void InOrderTraversal();    //中序遍历
};

//下面三行是手动内存池管理用的
SBNode mem[MaxN];
PSBNode stack[MaxN];
int memtop,stacktop;

//下面两行是给中序遍历用的
KeyType ans[MaxN];
int index;

void DeleteSBNode(PSBNode node)  //将节点放入回收队列
{
    stack[++stacktop]=node;
}

PSBNode NewSBNode()              //从回收队列或者内存池中分配新节点
{
    PSBNode res;
    if (stacktop) res=stack[stacktop--];
    else res=&mem[memtop++];
    return res;
}

void SBTree::LeftRotate(SBNode *&root)
{
    SBNode *tmp=root->rchild;
    root->rchild=tmp->lchild;
    tmp->lchild=root;
    tmp->size=root->size;
    root->size=(root->lchild->size)+(root->rchild->size)+1;
    root=tmp;
}


void SBTree::RightRotate(SBNode *&root)
{
    SBNode *tmp=root->lchild;
    root->lchild=tmp->rchild;
    tmp->rchild=root;
    tmp->size=root->size;
    root->size=(root->lchild->size)+(root->rchild->size)+1;
    root=tmp;
}

void SBTree::Maintain(SBNode *&root,bool style)
{
    if (root==_null) return;
    if (!style)
    {
        if      (root->lchild->lchild->size > root->rchild->size) RightRotate(root);
        else if (root->lchild->rchild->size > root->rchild->size)
        {
            LeftRotate(root->lchild);
            RightRotate(root);
        }
    else return;
    }
    else
    {
        if      (root->rchild->rchild->size > root->lchild->size) LeftRotate(root);
        else if (root->rchild->lchild->size > root->lchild->size)
        {
            RightRotate(root->rchild);
            LeftRotate(root);
        }
        else return;
    }
    Maintain(root->lchild,false);
    Maintain(root->rchild,true);
    Maintain(root,false);
    Maintain(root,true);
}

void SBTree::DoInsert(SBNode *&root,KeyType key)
{
    if (root==_null)
    {
        root=NewSBNode();
        root->lchild=_null;
        root->rchild=_null;
        root->size=1;
        root->key=key;
        return;
    }
    root->size++;
    if (key< root->key) DoInsert(root->lchild,key);
    else                DoInsert(root->rchild,key);
    Maintain(root,key>=root->key);
}

void SBTree::DoDelete(SBNode *&root,KeyType key)
{
    if (root==_null) return;
    root->size--;
    if (root->key==key)
    {
        SBNode *tmp;
        if (root->lchild!=_null && root->rchild==_null)
        {
            tmp=root;
            root=tmp->lchild;
            DeleteSBNode(tmp);
        }
        else if (root->lchild== _null && root->rchild==_null)
        {
            tmp=root;
            root=_null;
            DeleteSBNode(tmp);
        }
        else
        {
            tmp=root->rchild;
            while (tmp->lchild!= _null) tmp=tmp->lchild;
            root->key=tmp->key;
            DoDelete(root->rchild,tmp->key);
        }
    }
    else if (key<root->key) DoDelete(root->lchild,key);
    else DoDelete(root->rchild,key);
}

void SBTree::ClearSubtree(SBNode *root)
{
    if (root!= _null)
    {
        ClearSubtree(root->lchild);
        ClearSubtree(root->rchild);
        DeleteSBNode(root);
    }
}

void SBTree::DoInOrderTraversal(SBNode *root)
{
    if (root!= _null)
    {
        DoInOrderTraversal(root->lchild);
        ans[index++]=root->key;
        DoInOrderTraversal(root->rchild);
    }
}

SBTree::SBTree()
{
    _null=new SBNode();
    root=_null;
    root->lchild=root->rchild=_null;
    root->size=0;
    memtop=stacktop=0;
}

SBTree::~SBTree()
{
    Clear();
}

void SBTree::Delete(KeyType key)
{
    DoDelete(root,key);
}

void SBTree::Insert(KeyType key)
{
    DoInsert(root,key);
}

KeyType SBTree::GetRank(int k)
{
    SBNode *tmp=root;
    while (1)
    {
        if (tmp->lchild && tmp->lchild->size+1==k) break;
        else if (tmp->lchild && k<=tmp->lchild->size) tmp=tmp->lchild;
        else
        {
            k=k-(tmp->lchild?tmp->lchild->size:0)-1;
            tmp=tmp->rchild;
        }
    }
    return tmp->key;
}

KeyType SBTree::GetMin()
{
    if (root==_null) return KeyType();
    SBNode *tmp=root;
    while (tmp->lchild!=_null) tmp=tmp->lchild;
    return tmp->key;
}

KeyType SBTree::GetMax()
{
    if (root==_null) return KeyType();
    SBNode *tmp=root;
    while (tmp->rchild!=_null) tmp=tmp->rchild;
    return tmp->key;
}

void SBTree::Clear()
{
    ClearSubtree(root);
    delete _null;
    memtop=stacktop=0;
}

void SBTree::InOrderTraversal()
{
    index=0;
    DoInOrderTraversal(root);
}

/*----------Size Balanced Tree Template----------*/
