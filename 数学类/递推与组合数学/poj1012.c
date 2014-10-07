#include<stdio.h>

int main()
{
    int Joseph[15]={0},k,n,m,i,ans[30];
    freopen("poj1012.txt","r",stdin);
    freopen("poj1012ans.txt","w",stdout);
    while (scanf("%d",&k) && k)
    {
        if (Joseph[k])  //已经有结果了，直接输出 
        {
       	    printf("%d\n",Joseph[k]);
       	    continue;
        }
        n=2*k;
        for (i=0;i<30;i++) ans[i]=0;  //初始化被杀列表 
        m=1;
        for (i=1;i<=k;i++)
        {
       	    ans[i]=(ans[i-1]+m-1)%(n-i+1);  //递推关系 
       	    if (ans[i]<k) //如果杀掉的是一个好人，那么m++ 
       	    {
   	        i=0;
   	        m++;
       	    }
        }
        Joseph[k]=m;
        printf("%d\n",Joseph[k]);
    }
    return 0;
}
