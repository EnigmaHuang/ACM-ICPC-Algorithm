////http://www.cnblogs.com/Booble/archive/2010/10/10/1847163.html 

#include <stdio.h>
#include <math.h>
#include <algorithm>

#define MaxN 5050
using namespace std;

struct TNode
{
    int l,r;
    int lcov,rcov;          //左右端点是否被覆盖
    int count,linecnt,len;  //被覆盖的次数，包含区间的数量，区间长度
}node[MaxN*3];

struct TScanSegment
{
    int x,y1,y2;
    int flag;     //flag：1=入边，-1=出边
    bool operator < (TScanSegment seg2) const //按x升序，x同入边在前 
    {
        if (this->x==seg2.x) return (this->flag>seg2.flag);
        else return (this->x<seg2.x);
    }
}seg[MaxN*2];

int y[MaxN*2];     //记录y坐标
int flag; 

void BuildTree(int left,int right,int u)
{
    int mid; 
    node[u].l=left;
    node[u].r=right;
    node[u].len=node[u].linecnt=node[u].count=0;
    if (left+1==right) return;
    mid=(left+right)/2;
    BuildTree(left,mid,u*2);
    BuildTree(mid,right,u*2+1);
}

void UpdateNode(int u)  //更新长度和包含区间数量 
{                   
    if (node[u].count>0) 
    {
        node[u].len=y[node[u].r]-y[node[u].l];
        node[u].linecnt=node[u].lcov=node[u].rcov=1;
    }
    else if (node[u].l+1==node[u].r)
    {
        node[u].len=0;
        node[u].linecnt=node[u].lcov=node[u].rcov=0;
    }
    else     //由左右子树的值确定当前点的值 
    {
        node[u].len=node[u*2].len+node[u*2+1].len;
        node[u].lcov=node[u*2].lcov;
        node[u].rcov=node[u*2+1].rcov;
        node[u].linecnt=node[u*2].linecnt+node[u*2+1].linecnt 
                       -node[u*2].rcov*node[u*2+1].lcov;
    }
}

void SegmentUpdate(int left,int right,int u)
{
    int mid;
    if (y[node[u].l]==left && y[node[u].r]==right)  //找到目标区间，更新之 
    {
        node[u].count+=flag;
        UpdateNode(u);
        return;
    }
    mid=y[(node[u].l+node[u].r)/2];
    //向子树更新 
    if (right<=mid) SegmentUpdate(left,right,u*2);
    else if (left>=mid) SegmentUpdate(left,right,u*2+1);
    else
    {
        SegmentUpdate(left,mid,u*2);
        SegmentUpdate(mid,right,u*2+1);
    }
    //子树更新完需要重新更新当前节点 
    UpdateNode(u);
}

int main ()
{
    int n,m,i,j,k;
    int x1,y1,x2,y2;
    int Perimeter;   //周长 
    int PreYCover;   //上一根扫描线位置Y轴覆盖长度和
    int NowParaXCnt; //当前平行于X轴的边的数量
    freopen("poj1177.txt","r",stdin);
    freopen("poj1177ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        m=0;
        for (i=0;i<n;i++)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            seg[m].x =x1;
            seg[m].y1=y1;
            seg[m].y2=y2;
            seg[m].flag=1;
            y[m++]=y1;
            seg[m].x =x2;
            seg[m].y1=y1;
            seg[m].y2=y2;
            seg[m].flag=-1;
            y[m++]=y2;
        }
        sort(y,y+m);
        sort(seg,seg+m);
        //离散化 
        k=1;
        for (i=1;i<m;i++) if (y[i]!=y[i-1]) y[k++]=y[i];
        
        BuildTree(0,k-1,1);
        
        Perimeter=0;
        PreYCover=0;
        NowParaXCnt=0;         
        for (i=0;i<m;i++)
        {
            flag=seg[i].flag;
            SegmentUpdate(seg[i].y1,seg[i].y2,1);
            //新增平行X轴的边的长度=当前扫描线上平行X轴的边数*x坐标改变值 
            if (i>0) Perimeter+=2*NowParaXCnt*(seg[i].x-seg[i-1].x);
            //新增平行Y轴的边的长度=扫描线前后位置中扫描覆盖长度之差的绝对值 
            Perimeter+=abs(node[1].len-PreYCover);   
            //更新Y轴覆扫描覆盖长度和平行X轴的边的长度 
            PreYCover=node[1].len;
            NowParaXCnt=node[1].linecnt;
        }
        printf("%d\n",Perimeter);
    }
    return 0;
}

