#include<stdio.h>
#define MaxN 102
long long c[MaxN][MaxN];  
  
void GetCList()
{  
    int i,j;  
    for (i=0;i<MaxN;i++) c[i][0]=1;  
    for (i=1;i<MaxN;i++)
        for (j=1;j<102;j++)  
            c[i][j]=c[i-1][j-1]+c[i-1][j];  
}  
  
int main()
{  
    int n,m;
    GetCList();  
    while (scanf("%d%d",&n,&m)!=EOF && n) 
        printf("%d things taken %d at a time is %d exactly.\n",n,m,c[n][m]);  
    return 0;
}
