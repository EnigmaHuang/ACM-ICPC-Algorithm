#include<stdio.h>

int main()
{
   int n,num,ans;
   scanf("%d",&n);
   while(n--)
   {
      scanf("%d",&num);
      ans=0;
      while (num>=5)
      {
         ans+=num/5;
         num/=5;
      }
      printf("%d\n",ans);
   }
   return 0;
}
