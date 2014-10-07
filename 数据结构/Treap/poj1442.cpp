#include<stdio.h>
#include<stdlib.h>

using namespace std;

#define INF  0x3f3f3f3f
#define MaxN 30001

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

int s[MaxN];

int main()
{
    int i,n,m,pos,newpos,k;
    freopen("poj1442.txt","r",stdin);
    freopen("poj1442ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        pos=0;
        k=1;
        for (i=0;i<n;i++) scanf("%d",&s[i]);
        for (i=0;i<m;i++)
        {
            scanf("%d",&newpos);
            while (pos<newpos) Treap.Insert(s[pos++]);
            printf("%d\n",Treap.GetKthMin(k++));
        }
    }
    return 0;
}
