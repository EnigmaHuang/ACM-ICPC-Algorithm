#include <stdio.h>
#include <string.h>

#define MaxN 75 

using namespace std;

int a[MaxN][MaxN],ans[MaxN],MOD;

inline int abs(int x) {return(x>0?x:-x);}

inline void swap(int &x, int &y) 
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

int GaussSolve(const int &row,const int &col)
{
    int i,j,k,id,l,lcm,x,y;
    for (i=j=0;i<row && j<col;i++,j++)  //i是当前行，j是当前主元位置 
    {
        id=i;
        //在剩下的行里找当前主元最大的，交换上来当前行 
        for (k=i+1;k<row;k++) if (abs(a[k][j])>abs(a[id][j])) id=k;
        for (k=i;k<=col;k++) swap(a[i][k],a[id][k]);
        //剩下的行里当前主元都被消掉了，主元向后移一位 
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
    //因为一定有解所以不判断了 
    for (i=row-1;i>=0;i--)
    {
        for (j=i+1;j<col-1;j++)
        {
       	    a[i][col-1]-=ans[j]*a[i][j];
       	    a[i][col-1]%=MOD;
        }
        while (a[i][col-1]%a[i][i]!=0) a[i][col-1]+=MOD;  //要取到整系数 
        ans[i]=a[i][col-1]/a[i][i];
        ans[i]=(ans[i]%MOD+MOD)%MOD;
    }
    return 0;
}

int main()
{
    int i,j,n,t;
    char c[100];
    freopen("poj2065.txt","r",stdin);
    freopen("poj2065ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&MOD);
        scanf("%s",c);
        n=strlen(c);
        memset(a,0,sizeof(a));
        for (i=0;i<n;i++) 
	{
	    if (c[i]=='*') a[i][n]=0;else a[i][n]=c[i]-'a'+1;
            a[i][0]=1;
            for (j=1;j<n;j++) a[i][j]=(a[i][j-1]*(i+1))%MOD;
        } 
	GaussSolve(n,n+1);
        for (i=0;i<n-1;i++) printf("%d ",ans[i]);
        printf("%d\n",ans[n-1]);
    }
    return 0;
} 
