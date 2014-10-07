#include<stdio.h>
#include<string.h>

#define MaxSize 3 

using namespace std;

/*----------Matrix Fast-Power Template Start----------*/

struct TMatrix
{
    int matrix[MaxSize][MaxSize];
    int r,c;
};

int MOD;

void ReadMatrix(TMatrix &src,int row,int column)
{
    int i,j;
    src.r=row;
    src.c=column;
    memset(src.matrix,0,sizeof(src.matrix)); 
    for (i=0;i<row;i++)
        for (j=0;j<column;j++)
        {
            scanf("%d",&src.matrix[i][j]);
            src.matrix[i][j]%=MOD;   //初始化要先模余 
        }
}

TMatrix Add(TMatrix &a,TMatrix &b)  //矩阵加法
{
    TMatrix res;
    int i,j;
    res.c=a.c;
    res.r=a.r;
    for (i=0;i<a.r;i++)
        for (j=0;j<a.c;j++)
        {
            res.matrix[i][j]=a.matrix[i][j]+b.matrix[i][j];
            res.matrix[i][j]%=MOD;   //加的时候也要模余
        }
    return res;
}

TMatrix Mul(TMatrix &a,TMatrix &b)  //矩阵乘法
{
    TMatrix res;
    int i,j,k;
    res.c=a.c;
    res.r=b.r;
    for (i=0;i<a.r;i++)
        for (j=0;j<b.c;j++)
        {
            res.matrix[i][j]=0;  //初始化矩阵c
            for (k=0;k<a.c;k++) res.matrix[i][j]+=a.matrix[i][k]*b.matrix[k][j];
            res.matrix[i][j]%=MOD;  //计算乘法的时候也要模余
        } 
    return res;
}

TMatrix Cal(int exp,TMatrix &src)   //矩阵幂
{
    TMatrix p,q;
    int i;
    p=src;     //p是初始矩阵
    q.c=p.c;
    q.r=p.r;
    memset(q.matrix,0,sizeof(q.matrix));
    for (i=0;i<MaxSize;i++) q.matrix[i][i]=1; //q初始化为单位阵 
    while(exp!=1)
    {
        if(exp&1)       
        {
            exp--;
            q=Mul(p,q);
        } 
        exp>>=1;   
        p=Mul(p,p);
    }
    p=Mul(p,q);
    return p;
}

/*----------Matrix Fast-Power Template Start----------*/

int main()
{
    int n;
    TMatrix a,ans;
    freopen("poj3070.txt","r",stdin);
    freopen("poj3070ans.txt","w",stdout);
    a.r=2;
    a.c=2;
    MOD=10000;
    while (scanf("%d",&n) && n!=-1)
    {
        a.matrix[0][0]=1;
        a.matrix[0][1]=1;
        a.matrix[1][0]=1;
        a.matrix[1][1]=0;
        if (n>=2) ans=Cal(n-1,a);
        else if (n==1) ans.matrix[0][0]=1;
        else if (n==0) ans.matrix[0][0]=0;
        printf("%d\n",ans.matrix[0][0]);
    }
    return 0;
}
