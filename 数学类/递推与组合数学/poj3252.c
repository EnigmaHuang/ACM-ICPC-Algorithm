#include<stdio.h>

#define MaxN 35

int c[MaxN][MaxN]={0};
int bin[MaxN];  //十进制n的二进制数

void MakeList()
{
    int i,j;
    for (i=0;i<=32;i++)
        for (j=0;j<=i;j++)
        {
            if (!j || i==j) c[i][j]=1;
            else c[i][j]=c[i-1][j-1]+c[i-1][j];
        }
}

int round(int n)
{
    int i,j,sum,zero;
    
    bin[0]=0;
	while (n)
    {
        bin[0]++;
        bin[bin[0]]=n%2;
        n/=2;
    }

    //计算长度小于bin[0]的所有二进制数中RN的个数
    sum=0;
    for (i=1;i<bin[0]-1;i++)
        for (j=i/2+1;j<=i;j++)
            sum+=c[i][j];
            
    ///计算长度等于bin[0]的所有二进制数中RN的个数
    zero=0;  //从高位向低位搜索过程中出现0的位的个数
    for (i=bin[0]-1;i>=1;i--)
    {
        if (bin[i]) for (j=(bin[0]+1)/2-(zero+1);j<=i-1;j++) sum+=c[i-1][j];
        else zero++;
    }
    return sum;
}

int main()
{
    int a,b;
    freopen("poj3252.txt","r",stdin);
    freopen("poj3252ans.txt","w",stdout);
    MakeList();
    while (scanf("%d%d",&a,&b)!=EOF) 
        printf("%d\n",round(b+1)-round(a));
}
