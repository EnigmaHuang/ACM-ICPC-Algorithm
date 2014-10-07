#include<stdio.h>
#include<string.h>

int SG[55][60005];

int GetSG(int i,int j)
{
    if (SG[i][j]!=-1) return SG[i][j];
    if (j==1)
    {
        SG[i][j]=GetSG(i+1,0);
        return SG[i][j];
    }     
    SG[i][j]=0;
    //某堆只有一个的取掉
    if (i>=1 && !GetSG(i-1,j)) SG[i][j]=1;
    //把不是1个的取走一个
    else if (j>=1 && !GetSG(i,j-1)) SG[i][j]=1;
    //把1个的合并给不是1个的
    else if (i>=1 && j>0 && !GetSG(i-1,j+1)) SG[i][j]=1;
    //把两个1个的合并，注意合并需要一步
    else if (i>=2 && ( (j==0 && !GetSG(i-2,j+2))
                     ||(j!=0 && !GetSG(i-2,j+3)) ) )
         SG[i][j]=1;
    return SG[i][j];
}

int main()
{
    int n,t,cases=0,k,one,sum;
    freopen("hdoj4111.txt","r",stdin);
    freopen("hdoj4111ans.txt","w",stdout);
    scanf("%d",&t);
    memset(SG,-1,sizeof(SG));
    while (t--)
    {
        scanf("%d",&n);
        one=0;
        sum=0;
        while (n--)
        {
            scanf("%d",&k);
            if (k==1) one++;
            else sum+=(k+1);
        }
        if (sum) sum--;
        printf("casese #%d: ",++cases);
        if (GetSG(one,sum)) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}
