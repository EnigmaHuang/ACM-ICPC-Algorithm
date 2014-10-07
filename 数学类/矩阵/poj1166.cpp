#include <stdio.h>
#include <string.h>

#define MaxN 10 
#define MOD 4 

using namespace std;

int ans[MaxN];

int a[MaxN][MaxN]=
{
//opt: 1 2 3 4 5 6 7 8 9 res
      {1,1,0,1,0,0,0,0,0,0}, 
      {1,1,1,0,1,0,0,0,0,0}, 
      {0,1,1,0,0,1,0,0,0,0},
      {1,0,0,1,1,0,1,0,0,0},
      {1,0,1,0,1,0,1,0,1,0},
      {0,0,1,0,1,1,0,0,1,0},
      {0,0,0,1,0,0,1,1,0,0},
      {0,0,0,0,1,0,1,1,1,0},
      {0,0,0,0,0,1,0,1,1,0},
      {0},
};

inline int abs(int x) {return(x>0?x:-x);}

inline void swap(int &x,int &y) 
{ 
    int z;
    z=x;x=y;y=z;
}

int GCD(int a,int b)
{
    if (b==0) return a;
    return GCD(b,a%b);
}

int LCM(int a,int b)
{
    return a*b/GCD(a,b);
}

void GaussSolve(const int &row,const int &col)
{
    int i,j,k,id,l,lcm,x,y;
    for (i=j=0;i<row && j<col;i++,j++)  //i是当前行，j是当前主元位置 
    {
        if (a[i][j]==0)
	{
            id=i;
            //在剩下的行里找当前主元最大的，交换上来当前行 
            for (k=i+1;k<row;k++) if (a[k][j]) {id=k;break;}
            for (k=i;k<=col;k++) swap(a[i][k],a[id][k]);
            //剩下的行里当前主元都被消掉了，主元向后移一位 
        }
	if (a[i][j]==0) 
	{ 
	    i--; 
	    continue; 
        }
        //向下消元 
        for (k=i+1;k<row;k++) if (a[k][j]!=0) //这里因题而改
        {
            lcm=LCM(a[k][j],a[i][j]);
            x=lcm/a[k][j];
            y=lcm/a[i][j];
            for (l=j;l<col;l++) a[k][l]=((a[k][l]*x-a[i][l]*y)%MOD+MOD)%MOD;  
	}
    }
    for (i=row-1;i>=0;i--)
    {
        for (j=i+1;j<col-1;j++) a[i][col-1]-=a[i][j]*ans[j];
        a[i][col-1]=(a[i][col-1]%MOD+MOD)%MOD;
        for (ans[i]=0;ans[i]<=3;ans[i]++)
            if ((ans[i]*a[i][i]%MOD+MOD)%MOD==a[i][col-1]) break;
        ans[i]=(ans[i]%MOD+MOD)%MOD;
    } 
}

int main()
{
    int i,j;
    freopen("poj1166.txt","r",stdin);
    freopen("poj1166ans.txt","w",stdout);
    for (i=0;i<9;i++)
    {
        scanf("%d",&j);
        a[i][9]=(4-j)%MOD;
    }
    GaussSolve(9,10);
    for (i=0;i<9;i++) for (j=1;j<=ans[i];j++) printf("%d ",i+1);
    return 0;
} 
