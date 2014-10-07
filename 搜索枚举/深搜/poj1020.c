#include<stdio.h>
#include<string.h>

#define MaxCakeSize 51
#define MaxNeedSize 11

int s,n;
int pos[MaxCakeSize],num[MaxNeedSize];

int DFS(int depth)
{
    int row,col,i,j,flag;
    if (depth==n) return 1;
    row=s;

    //找已用宽度最小的一行
    for (i=1;i<=s;i++) if (pos[i]<row)
    {
        row=pos[i];
        col=i;

    
    //剪枝1：从最大的方块开始找，因为这样最容易出现矛盾，从而回溯
    for (i=10;i>0;i--) if (num[i] && (row+i-1<=s) && (col+i-1<=s))
    {
        flag=1;
        
        //从当前行向下，看已用位置是否对齐，若不对齐则显然不行
        for (j=col+1;j<=col+i-1;j++) if (pos[j]!=pos[col]) flag=0;
        if (!flag) continue;
        
        //放入新方格
        for (j=col;j<=col+i-1;j++) pos[j]+=i;
        num[i]-=1;
        
        if (DFS(depth+1)) return 1;  //下一层搜索，成功了直接返回，也算一个剪枝吧
        else  //失败了，操作回滚
        {
            num[i]+=1;
            for (j=col;j<=col+i-1;j++) pos[j]-=i;
        }
    }
    
    return 0;
}

int main()
{
    int i,cases,total,size,flag;
    freopen("poj1020.txt","r",stdin);
    freopen("poj1020ans.txt","w",stdout);
    scanf("%d",&cases);
    while (cases--)
    {
        scanf("%d%d",&s,&n);
        memset(num,0,sizeof(num));
        for (i=1;i<=s;i++) pos[i]=1;
        total=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&size);
            num[size]++;
            total+=size*size;
        }
        flag=0;
        if (total==s*s) flag=DFS(0);  //面积不同，不需要搜索直接否定
        if (flag) printf("KHOOOOB!\n");
        else printf("HUTUTU!\n");
    }
    return 0;
}
