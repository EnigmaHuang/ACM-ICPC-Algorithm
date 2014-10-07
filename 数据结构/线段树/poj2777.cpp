#include<stdio.h>
#define MaxN 100005

using namespace std;

struct
{
    int l,r;
    int val;    //32位的int型每一位对应一种颜色，用位运算代替bool col[32]
    int cover;  //表示这个区间都被涂上同一种颜色，线段树效率的体现，否则插入就是0(n)了
}node[3*MaxN];

void swap(int &a, int &b)
{
    int tmp=a;a=b;b=tmp;
}

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].val=1;         //开始时都为涂有颜色1
    node[u].cover=1;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PushDown(int u)       //延迟操作
{
    node[u].cover=0;
    node[u*2].val=node[u].val;
    node[u*2].cover=1;
    node[u*2+1].val=node[u].val;
    node[u*2+1].cover=1;
}

void SegmentUpdata(int left,int right,int newvalue,int u)
{
    if (left<=node[u].l && right>=node[u].r)
    {
        node[u].val=newvalue;
        node[u].cover=1;
        return;
    }
    if (node[u].val==newvalue) return;     //剪枝
    if (node[u].cover) PushDown(u);
    //node[u].col |= val;   不行，因为新加入的颜色可能会把node[u].val中的某些颜色覆盖掉
    if (left<=node[u*2].r)    SegmentUpdata(left,right,newvalue,u*2);
    if (right>=node[u*2+1].l) SegmentUpdata(left,right,newvalue,u*2+1);

    //下面这一句是新加的
    node[u].val=node[u*2].val | node[u*2+1].val;   //最后递归回来再更改父节点的颜色
}

void SegmentSum(int left,int right,int &sum,int u)
{
    if (node[u].cover)      //这个区间全部为1种颜色，不在分隔区间
    {         
        //sum+=node[u].val;
        sum |= node[u].val; //颜色种类相加位运算代码
        return;
    }
    if (left<=node[u].l && right>=node[u].r)
    {
        //sum+=node[u].val;
        sum |= node[u].val;
        return;
    }
    if (left<=node[u*2].r)    SegmentSum(left,right,sum,u*2);
    if (right>=node[u*2+1].l) SegmentSum(left,right,sum,u*2+1);
}

int BinSum(int sum)           //求int型的sum对应的颜色数量
{
    int ans=0;
    while (sum)
    {
        if (sum%2) ans++;  
        sum=sum/2;        
    }
    return ans;
}

int main()
{
    int n,t,m,sum;
    freopen("poj2777.txt","r",stdin);
    freopen("poj2777ans.txt","w",stdout);
    scanf("%d%d%d",&n,&t,&m);
    BuildTree(1,n,1);
    while (m--)
    {
        getchar();
        int a,b,c;
        char ope;
        scanf("%c", &ope);
        if(ope == 'C')
        {
            scanf("%d%d%d",&a,&b,&c);
            if (b<a) swap(a,b);            //有可能b<a
            SegmentUpdata(a,b,1<<(c-1),1); //int型的右起第c位（第c种颜色）变为1
        }
        else
        {
            scanf("%d%d",&a,&b);
            if (b<a) swap(a,b);
            sum=0;
            SegmentSum(a,b,sum,1);
            printf("%d\n",BinSum(sum));
        }
    }
    return 0;
}
