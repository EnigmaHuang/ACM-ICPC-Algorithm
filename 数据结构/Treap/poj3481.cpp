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
        int id[MaxN];
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
        void DoInsert(int &x,int k,int tid)
        {
            if (x)
            {
                if (key[x]==k) cnt[x]++;
                else
                {
                    int t=key[x]<k;
                    DoInsert(childs[x][t],k,tid);
                    if (priority[childs[x][t]]<priority[x]) Rotate(x,t);
                }
            }
            else
            {
                x=TreapCnt++;
                key[x]=k;
                cnt[x]=1;
                id[x]=tid;
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
        int DoGetKthID(int &x,int k)
        {
            if (k<=size[childs[x][0]]) return DoGetKthID(childs[x][0],k);
            k-=size[childs[x][0]]+cnt[x];
            if (k<=0) return id[x];
            return DoGetKthID(childs[x][1],k);
        }
        int DoGetKth(int &x,int k)
        {
            if (k<=size[childs[x][0]]) return DoGetKth(childs[x][0],k);
            k-=size[childs[x][0]]+cnt[x];
            if (k<=0) return key[x];
            return DoGetKth(childs[x][1],k);
        }
    public:
        TTreap()
        {
            root=0;
            NodeNum=0;
            TreapCnt=1;
            priority[0]=INF;
            size[0]=0;
        }
        void Insert(int k,int tid)  //插入键值k
        {
            DoInsert(root,k,tid);
            NodeNum++;
        }
        void Erase(int k)  //删除键值k
        {
            DoErase(root,k);
            NodeNum--;
        }
        int GetKthMinID(int k) {return DoGetKthID(root,k);}           //获取第K小的的ID
        int GetKthMaxID(int k) {return DoGetKthID(root,NodeNum-k+1);} //获取第K大的的ID
        int GetKthMin(int k) {return DoGetKth(root,k);}           //获取第K小的
        int GetKthMax(int k) {return DoGetKth(root,NodeNum-k+1);} //获取第K大的
}Treap;

int main()
{
    int i,c,id,pri,n;
    freopen("poj3481.txt","r",stdin);
    freopen("poj3481ans.txt","w",stdout);
    n=0;
    while (scanf("%d",&c) && c!=0)
    {
        if (c==1)
        {
            scanf("%d%d",&id,&pri);
            Treap.Insert(pri,id);
            n++;
        }
        if (c==2)
        {
            if (n==0)
            {
                    n++;
                    Treap.Insert(0,0);
            }
            printf("%d\n",Treap.GetKthMaxID(1));
            Treap.Erase(Treap.GetKthMax(1));
            n--;
        }
        if (c==3)
        {
            if (n==0)
            {
                    n++;
                    Treap.Insert(0,0);
            }
            printf("%d\n",Treap.GetKthMinID(1));
            Treap.Erase(Treap.GetKthMin(1));
            n--;
        }
    }
    return 0;
}
