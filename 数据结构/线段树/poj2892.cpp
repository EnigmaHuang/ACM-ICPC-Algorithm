#include <stdio.h>
#include <string.h>
#include <stack>

using namespace std;

#define MaxN 50005
#define Max(a,b) (a)>(b)?(a):(b)

struct TNode
{
    int l,r;
    int lma,rma,ma;
}node[MaxN*3];

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].lma=node[u].rma=node[u].ma=right-left+1;
    if (left==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

void PointUpdate(int pos,int u,int flag)
{
    int mid,a,b,c;
    if (node[u].l==node[u].r)  //到叶子节点了，直接更新之
    {
        node[u].lma=node[u].ma=node[u].rma=flag;
        return;
    }

    mid=(node[u].l+node[u].r)/2;

    if (pos<=mid) PointUpdate(pos,u*2,flag);
    else PointUpdate(pos,u*2+1,flag);

    //左子树全空，则此节点的左连续数等于左子树长度+右子树左连续长度
    //否则节点的左连续数=左子树的左连续数
    if (node[u*2].ma==node[u*2].r-node[u*2].l+1)
         node[u].lma=node[u*2].ma+node[u*2+1].lma;
    else node[u].lma=node[u*2].lma;

    //更新右连续数，原理同左连续数
    if (node[u*2+1].ma==node[u*2+1].r-node[u*2+1].l+1)
         node[u].rma=node[u*2+1].ma+node[u*2].rma;
    else node[u].rma=node[u*2+1].rma;

    a=node[u*2].rma+node[u*2+1].lma;    //左右子树相接触的连续数
    b=Max(node[u*2].ma,node[u*2+1].ma); //左右子树各自内部连续数的较大者
    //c=Max(node[u].lma,node[u].rma);     //此节点左右连续数的较大者
    node[u].ma=Max(a,b);
}

int PointQuery(int pos,int u)
{
    int mid;
    //如果该节点的区间全满或者全空，直接返回
    if (node[u].l==node[u].r || node[u].ma==0
     || node[u].ma==node[u].r-node[u].l+1) return node[u].ma;

    mid=(node[u].l+node[u].r)/2;
    if (pos<=mid)  //目标节点在当前节点的左子树
    {
            //目标节点在左子树的到右侧连续区间内
            //返回左子树的到右侧连续区间长度+右子树的从左区间开始连续长度
            //否则进入区间搜索
            if (pos>=node[u*2].r-node[u*2].rma+1)
             return node[u*2].rma+node[u*2+1].lma;
            else return PointQuery(pos,u*2);
    }
    else           //在右子树
    {
            //目标节点在右子树的从左区间开始的连续区间内
        //返回同上，否则进入区间搜索
            if (pos<=node[u*2+1].l+node[u*2+1].lma-1)
             return node[u*2].rma+node[u*2+1].lma;
            else return PointQuery(pos,u*2+1);
    }
}

int main()
{
    int n,m,x;
    char s[15];
    stack<int> st;
    
    freopen("poj2892.txt","r",stdin);
    freopen("poj2892ans.txt","w",stdout);
    scanf("%d %d",&n,&m);
    
    BuildTree(1,n,1);
    while(!st.empty()) st.pop();

    while(m--)
    {
        scanf("%s",s);
        if (s[0]=='D')
        {
            scanf("%d",&x);
            st.push(x);
            PointUpdate(x,1,0);
        }
        else if (s[0]=='R')
        {
            x=st.top();
            st.pop();
            PointUpdate(x,1,1);
        }
        else
        {
            scanf("%d",&x);
            printf("%d\n",PointQuery(x,1));
        }
    }
    return 0;
}
