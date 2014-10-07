#include<stdio.h>
#include<string.h>

#define MaxSize 102 

using namespace std; 

struct TMatrix
{
    __int64 matrix[MaxSize][MaxSize];
    __int64 r,c;
};

TMatrix Mul(TMatrix &a,TMatrix &b) 
{
    TMatrix res;
    __int64 i,j,k;
    res.r=a.r;
    res.c=b.c;
    memset(res.matrix,0,sizeof(res.matrix));
    for (i=0;i<a.r;i++)
        for (k=0;k<a.c;k++) if (a.matrix[i][k])//优化
        {
       	    for (j=0;j<b.c;j++) res.matrix[i][j]+=a.matrix[i][k]*b.matrix[k][j];
        }    
    return res;
}

TMatrix peanut,opt;
__int64 n,m,k;

void InitMatrix()
{
    __int64 i;
    peanut.r=1;
    peanut.c=n+1;
    memset(peanut.matrix,0,sizeof(peanut.matrix));
    peanut.matrix[0][n]=1;
    opt.r=n+1;
    opt.c=n+1;
    memset(opt.matrix,0,sizeof(opt.matrix));
    for (i=0;i<n+1;i++) opt.matrix[i][i]=1;    
}

int main() 
{
    __int64 i,x,y,swap;
    char c;
    freopen("poj3735.txt","r",stdin);
    freopen("poj3735ans.txt","w",stdout);
    while (scanf("%I64d %I64d %I64d\n",&n,&m,&k)!=EOF)
    {
        if (n==0 && m==0 && k==0) break;
        InitMatrix();
    
        while(k--)
        {
            scanf("%c",&c);
            if(c=='g')
            {
                 scanf("%I64d\n",&x);//给x一颗花生米
                 opt.matrix[n][x-1]++;
            }
            else
            if(c=='e')
            {
                 scanf("%I64d\n",&x);//x吃掉所有的花生米
                 for (i=0;i<=n;i++) opt.matrix[i][x-1]=0;
            }
            else
            {
                 scanf("%I64d %I64d\n",&x,&y);//交换x与y的花生米
                 for (i=0;i<=n;i++)
                 {
                     swap=opt.matrix[i][x-1];
                     opt.matrix[i][x-1]=opt.matrix[i][y-1];
                     opt.matrix[i][y-1]=swap;
                 }
            }
        }
        while (m)          
        {
            if (m&1) peanut=Mul(peanut,opt);   
            m>>=1;
            opt=Mul(opt,opt);
        }
        printf("%I64d",peanut.matrix[0][0]);
        for (i=1;i<n;i++) printf(" %I64d",peanut.matrix[0][i]);
        printf("\n");
    }
    return 0;
}
