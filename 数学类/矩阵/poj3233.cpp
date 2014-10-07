#include<stdio.h>
#include<string.h>

#define MaxSize 70

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

int n,k;
TMatrix a,sa,sb;

/* 递归调用的写法*/  
TMatrix MatrixSum(int k)
{
    if (k==1) return a; //做到最底层就将矩阵a返回就好
    TMatrix tmp,tnow,tmp2;
    tmp.r=n;
    tmp.c=n;
    tmp=MatrixSum(k/2);
    if(k&1)  //如果k是奇数
    {
        tnow=Cal(k/2+1,a);
        tmp2=Mul(tmp,tnow);
        tmp=Add(tmp,tmp2);
        tmp=Add(tnow,tmp);
    }  
    else    //如果k是偶数
    {
        tnow=Cal(k/2,a);
        tmp2=Mul(tmp,tnow);
        tmp=Add(tmp,tmp2);
    }
    return tmp;
}


int main()
{
    int i,j;
    freopen("poj3233.txt","r",stdin);
    freopen("poj3233ans.txt","w",stdout); 
    while(scanf("%d%d%d",&n,&k,&MOD)!=EOF)
    {
        ReadMatrix(a,n,n);
        //sb=MatrixSum(k); 二分递归的写法 
        a.c+=n;
        a.r+=n;
        for (i=0;i<n;i++)
        {
            a.matrix[i+n][i]=1;
            a.matrix[i+n][i+n]=1;
        }
        sa=Cal(k+1,a);
        for (i=0;i<n;i++) sa.matrix[i+n][i]=(sa.matrix[i+n][i]-1+MOD)%MOD;
        for (i=0;i<n;i++)
        {
            for (j=0;j<n-1;j++) printf("%d ",sa.matrix[i+n][j]%MOD);
            printf("%d\n",sa.matrix[i+n][n-1]%MOD);
        }
    }
    return 0;
}
