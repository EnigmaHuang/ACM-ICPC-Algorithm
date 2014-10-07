#include<stdio.h>

//2的幂
int pow2[15]={2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};

/*
  n=海盗数，m=金币数，p=取第p个人的结果，返回 
  的是第p个人能拿多少钱，-1表示一定会死 
*/
int Solve(int n,int m,int p)
{
    int i,t;
    //金币够贿赂的情况
    if (n<=2*m)
    {
        //不是决策者，而且奇偶性相同，都能被贿赂
        if (n!=p && (n%2==p%2)) return 1;
        //剩下的都是决策者拥有
        else if (n==p) return (m-(n-1)/2);
        //其余人分不到金币，他们的决策不影响全局
        else return 0;
    }
    //金币够贿赂但决策者不能拿金币
    else if (n==2*m+1)
    {
        if (p<2*m && p&1) return 1; 
        else return 0;
    }
    t=n-2*m;
    //剩下的是最多可以保命的情况，对于决策者来说，肯定没有金币
    for (i=0;i<14;i++) if (t==pow2[i]) return 0; //2*m+2^k的决策者可以保命，但拿不到钱 
    for (i=1;i<14;i++) if (t<pow2[i])
    {
        //不是2*m+2^k的决策者必死
        if (p>2*m+pow2[i-1] && p<2*m+pow2[i]) return -1;
        else return 0;
    }
}

int main()
{
    int t,n,m,p,ans;
    scanf("%d",&t);
    freopen("hdoj1538.txt","r",stdin);
    freopen("hdoj1538ans.txt","w",stdout);
    while (t--)
    {
        scanf("%d%d%d",&n,&m,&p);
        ans=Solve(n,m,p);
        if (ans>=0) printf("%d\n",ans); else printf("Thrown\n");
    }
    return 0;
}   
