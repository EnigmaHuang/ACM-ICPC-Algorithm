#include <stdio.h>
#include <string.h>

using namespace std;

const int Max = 31;

int n,a[Max][Max],start[Max],end[Max];

inline int abs(int x) {return(x>0?x:-x);}

inline void swap(int &x, int &y) 
{ 
    int z;
    z=x;x=y;y=z;
}

int GaussSolve(int &row,int &col)
{
    int i,j,k,id,l;
    for (i=j=0;i<row && j<col;i++,j++)  //i是当前行，j是当前主元位置 
    {
        id=i;
        //在剩下的行里找当前主元最大的，交换上来当前行 
        for (k=i+1;k<row;k++) if(abs(a[k][j])>abs(a[id][j])) id=k;
        for (k=j;k<=col;k++) swap(a[i][k],a[id][k]);
        //剩下的行里当前主元都被消掉了，主元向后移一位 
	if (a[i][j]==0) 
	{ 
	    i--; 
	    continue; 
        }
        //向下消元 
        for (k=i+1;k<row;k++) 
        {
           if (a[k][j]==0) continue;
           for (l=j;l<=n;l++) 
	       a[k][l]=(a[k][l]-a[i][l]+2)%2; //这里是因题而改写了 
        }
   }
   for (k=i;k<row;k++) if (a[k][col]!=0) return(-1);
   return (1<<(col-i));
}
int main()
{
    int t,i,j,k,ans;
    freopen("poj1830.txt","r",stdin);
    freopen("poj1830ans.txt","w",stdout);
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++) scanf("%d",&start[i]);
        for (i=0;i<n;i++) scanf("%d",&end[i]);
        memset(a,0,sizeof(a));
        for (i=0;i<n;i++)
        {
            a[i][n]=(start[i]-end[i]+2)%2;
            a[i][i]=1;
        }
        while (scanf("%d%d",&k,&j) && k && j) 
	    a[j-1][k-1]=1;
        ans=GaussSolve(n,n);
        if (ans==-1) printf("Oh,it's impossible~!!\n");
        else printf("%d\n",ans);
    }
    return 0;
}
