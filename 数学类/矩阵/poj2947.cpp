#include <stdio.h>
#include <string.h>
#include <math.h>

#define MaxN 305 

#define MOD 7

using namespace std;

int a[MaxN][MaxN],ans[MaxN];

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
        for (k=i+1;k<row;k++) if (fabs(a[k][j])>fabs(a[id][j])) id=k;
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
            for (l=j;l<=col;l++) a[k][l]=((a[k][l]*x-a[i][l]*y)%MOD+MOD)%MOD;
        }
    }
    for (k=i;k<row;k++) if (a[k][col]!=0) return -1;
    if (i<col) return (col-i);
    for (i=col-1;i>=0;i--)
    {
        for (j=i+1;j<col;j++)
            a[i][col]=((a[i][col]-a[i][j]*ans[j])%MOD+MOD)%MOD;
        for (j=3;j<=9;j++)
            if ((j*a[i][i])%MOD==a[i][col]) 
	    {
	    	ans[i]=j;
	    	break;
	    }
    } 
    return 0;
}

const char days[7][4]={"MON","TUE","WED","THU","FRI","SAT","SUN"};

int main()
{
    int i,j,n,m,cnt,pos1,pos2,type,rank;
    char c1[4],c2[4];
    freopen("poj2947.txt","r",stdin);
    freopen("poj2947ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF && (m||n))
    {
        memset(a,0,sizeof(a));
        for (i=0;i<m;i++)
        {
       	    scanf("%d %s %s",&cnt,c1,c2);
       	    for (j=0;j<7;j++)
            {
                if (strcmp(c1,days[j])==0) pos1=j;
                if (strcmp(c2,days[j])==0) pos2=j;
            } 
            a[i][n]=(pos2-pos1+1+MOD)%MOD;
            for (j=0;j<cnt;j++)
            {
                scanf("%d",&type);
                a[i][type-1]++;
            }
            for (j=0;j<=n;j++) a[i][j]%=MOD;
        }
        rank=GaussSolve(m,n);
        if (rank==-1) printf("Inconsistent data.\n");
        if (rank>=1) printf("Multiple solutions.\n");
        if (rank==0)
        {
            for (j=0;j<n-1;j++) printf("%d ",ans[j]);
            printf("%d\n",ans[n-1]);
        }
    }
    return 0;
} 
