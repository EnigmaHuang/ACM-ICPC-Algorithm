#include<stdio.h>
#include<stdlib.h>

using namespace std;

#define INF  0x3f3f3f3f
#define MaxN 100001

class TTreap
{
    private:
        int root,TreapCnt,NodeNum;  //NodeNum：当前树中有多少个节点
        int key[MaxN];              //节点键值
        int priority[MaxN];         //优先级，用于加速
        int childs[MaxN][2];        //左右孩子的位置
        int cnt[MaxN];              //
        int size[MaxN];             //
        void Update(int x)
        {
            size[x]=size[childs[x][0]]+cnt[x]+size[childs[x][1]];
        }
        void Rotate(int &x,int t)
        {
            int y=childs[x][t];
            childs[x][t]=childs[y][1-t];
            childs[y][1-t]=x;
            Update(x);
            Update(y);
            x=y;
        }
        void DoInsert(int &x,int k)
        {
            if (x)
            {
                if (key[x]==k) cnt[x]++;
                else
                {
                    int t=key[x]<k;
                    DoInsert(childs[x][t],k);
                    if (priority[childs[x][t]]<priority[x]) Rotate(x,t);
                }
            }
            else
            {
                x=TreapCnt++;
                key[x]=k;
                cnt[x]=1;
                priority[x]=rand();
                childs[x][0]=childs[x][1]=0;
            }
            Update(x);
        }
        void DoErase(int &x,int k)
        {
            if (key[x]==k)
            {
                if (cnt[x]>1) cnt[x]--;
                else
                {
                    if (childs[x][0]==0&&childs[x][1]==0)
                    {
                        x=0;
                        return;
                    }
                    int t=priority[childs[x][0]]>priority[childs[x][1]];
                    Rotate(x,t);
                    DoErase(x,k);
                }
            }
            else DoErase(childs[x][key[x]<k],k);
            Update(x);
        }
        int DoGetKth(int &x,int k)
        {
            if (k<=size[childs[x][0]]) return DoGetKth(childs[x][0],k);
            k-=size[childs[x][0]]+cnt[x];
            if (k<=0) return key[x];
            return DoGetKth(childs[x][1],k);
        }
    public:
            void Reset()
            {
            root=0;
            NodeNum=0;
            TreapCnt=1;
            priority[0]=INF;
            size[0]=0;
            }
        TTreap(){Reset();}
        void Insert(int k)  //插入键值k
        {
            DoInsert(root,k);
            NodeNum++;
        }
        void Erase(int k)  //删除键值k
        {
            DoErase(root,k);
            NodeNum--;
        }
        int GetKthMin(int k) {return DoGetKth(root,k);}           //获取第K小的
        int GetKthMax(int k) {return DoGetKth(root,NodeNum-k+1);} //获取第K大的
}Treap;

struct TQuery
{
    int l,r,k,id;
}que[50001];

int rank[MaxN],ans[MaxN];

void QSort(TQuery q[],int l,int r)
{
    int i=l,j=r,mid=q[(l+r)/2].l;
    TQuery swap;
    while (i<=j)
    {
        while (q[i].l<mid) i++;
        while (q[j].l>mid) j--;
        if (i<=j)
        {
            swap=q[i];
            q[i]=q[j];
            q[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(q,i,r);
    if (l<j) QSort(q,l,j);
}

int main()
{
    int n,m,i,j,l,r,k,tmp;
    freopen("poj2761.txt","r",stdin);
    freopen("poj2761ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        Treap.Reset();
        for (i=1;i<=n;i++) scanf("%d",&rank[i]);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&que[i].l,&que[i].r,&que[i].k);
            if (que[i].l>que[i].r)
            {
                tmp=que[i].l;
                que[i].l=que[i].l=r;
                que[i].r=tmp;
            }
            que[i].id=i;
        }
        QSort(que,1,m);
        for (j=que[1].l;j<=que[1].r;j++) Treap.Insert(rank[j]);
        ans[que[1].id]=Treap.GetKthMin(que[1].k);
        for (i=2;i<=m;i++)
        {
            if (que[i].l>que[i-1].r)
            {
                for (j=que[i-1].l;j<=que[i-1].r;j++) Treap.Erase(rank[j]);
                for (j=que[i].l;j<=que[i].r;j++) Treap.Insert(rank[j]);
                ans[que[i].id]=Treap.GetKthMin(que[i].k);
            }
            else
            {
                for (j=que[i-1].l;j<que[i].l;j++) Treap.Erase(rank[j]);
                for (j=que[i-1].r+1;j<=que[i].r;j++) Treap.Insert(rank[j]);
                ans[que[i].id]=Treap.GetKthMin(que[i].k);
            }
        }
        for (i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
    return 0;
}
