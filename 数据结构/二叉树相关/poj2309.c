#include<stdio.h>

int main()
{
    int n,t,i,min,max;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        i=n&-n;      //这里用到树状数组里面的求最低位1的方法
        max=n|(i-1); //将最后一个1后面所有0变成1
        min=n-i+1;   //将最后一个1向后移动到末尾
        printf("%d %d\n",min,max);
    }
    return 0;
}
