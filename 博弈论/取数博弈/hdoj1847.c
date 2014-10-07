#include<stdio.h>

/*
  这题用SG函数打个表就可以发现规律了
  这里打表略去，可以见hdoj 1536那题模板
*/

int main()
{
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        if (n%3==0) printf("Cici\n");
        else printf("Kiki\n");
    }
    return 0;
}
