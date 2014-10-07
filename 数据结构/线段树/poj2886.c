#include <stdio.h>
#include <string.h>

#define MaxN 500005

struct line
{
    int l,r,val;
}node[MaxN*3];

int n,k;
int MaxID,MaxNum;   //约数个数最多的编号，约数个数的最大值
int div[MaxN];      //每个数的约数个数

void GetDivision()  //预处理所有数的约数个数
{
    int i,j;
    memset(div,0,sizeof(div));
    for (i=1;i<=n;i++)
    {
        div[i]++;
        for (j=i*2;j<=n;j+=i) div[j]++;
    }
    MaxID=1;
    MaxNum=div[1];
    for (i=2; i <= n; i++) if (div[i]>MaxNum)
    {
        MaxNum=div[i];
        MaxID=i;
    }
}

void BuildTree(int left,int right,int u)
{
    int mid;
    node[u].l=left;
    node[u].r=right;
    node[u].val=right-left+1;
    if (left==right) return ;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid+1,right,u*2+1);
}

int QueryPos(int k,int u) //求以u为根节点的子树中第k个数在数组中的位置
{
    node[u].val--;       //空位少1
    if (node[u].l==node[u].r) return node[u].l;

    //向子树搜索
    if (k<=node[u*2].val) return QueryPos(k,u*2);
    else return QueryPos(k-node[u*2].val,u*2+1);
}

char name[MaxN][15];
int  card[MaxN];

int main()
{
    int i,pos;
    freopen("poj2886.txt","r",stdin);
    freopen("poj2886ans.txt","w",stdout);
    while(scanf("%d %d",&n,&k)!=EOF)
    {
        GetDivision();
        for (i=1;i<=n;i++) scanf("%s %d",name[i],&card[i]);

        BuildTree(1,n,1);

        for (i=0;i<MaxID;i++)   //出圈MaxID即可，就能找出第MaxID次出圈的人的实际位置
        {
            pos=QueryPos(k,1);  //找到原始位置，顺便踢人出圈
            n--;                //出圈以后人数减1
            if (n==0) break;
            //求下一轮的出圈位置是剩下数组中第k个的k值
            if (card[pos]>0) k=(k-1+card[pos]-1)%n+1;
            else k=((k-1+card[pos])%n+n)%n+1;
        }
        printf("%s %d\n",name[pos],MaxNum);
    }
    return 0;
}
