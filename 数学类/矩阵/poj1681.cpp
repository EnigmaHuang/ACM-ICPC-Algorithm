#include<stdio.h>
#include<string.h>

#define MaxN 15*15+5
#define inf 0x3f3f3f3f

int a[MaxN][MaxN]; 
int ans[MaxN];
int move[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

void Swap(int &a,int &b)
{
    int x;
    x=a;a=b;b=x;
} 

int GaussSolve(int row,int col)
{
    int i,j,k,id,l,swap,lcm,tmp,x,y;
    for (i=j=0;i<row && j<col;i++,j++)  //i是当前行，j是当前主元位置 
    {
        id=i;
        //在剩下的行里找当前主元最大的，交换上来当前行 
        for (k=i+1;k<row;k++) if(a[k][j]>a[id][j]) id=k;
        if (id!=i) for (k=j;k<=col;k++) Swap(a[i][k],a[id][k]);
        //剩下的行里当前主元都被消掉了，主元向后移一位 
        if (a[i][j]==0) 
	{ 
            i--; 
            continue; 
        }
        //向下消元 
        for (k=i+1;k<row;k++) if (a[k][j]) //这里因题而改
            for (l=j;l<=col;l++) a[k][l]=a[k][l]^a[i][l];
    }
    
    for (j=0;j<row;j++) if (a[j][col-1] && a[j][j]==0) return inf;
    
    tmp=0;
    for (i=i-1;i>=0;i--)
    {
        for (j=i+1;j<col;j++) a[i][col-1]^=(a[i][j]&&a[j][col-1]);
        if (a[i][col-1]) tmp++;
    }
    return tmp;
}

int n; 

int main()
{
    int cases,i,j,t=0,k,ty,tx,res;
    char c;
    freopen("poj1681.txt","r",stdin);
    freopen("poj1681ans.txt","w",stdout);
    scanf("%d",&cases);
    while (cases--)
    {
        scanf("%d\n",&n);
        memset(a,0,sizeof(a));
        for (i=0;i<n;i++)
        {
            for (j=0;j<n;j++)
            {
       	        c=getchar();
       	        if (c=='w') a[i*n+j][n*n]=1;
       	        a[i*n+j][i*n+j]=1;
       	        for (k=0;k<4;k++)
                {
                    tx=i+move[k][0];
                    ty=j+move[k][1];
                    if (!(tx>=0 && tx<n && ty>=0 && ty<n)) continue;
                    a[tx*n+ty][i*n+j]=1;
                }
            }
            getchar();
        }
        res=GaussSolve(n*n,n*n+1);
        if (res==inf) printf("inf\n");
        else printf("%d\n",res);
    }
    return 0;
}
