#include<stdio.h>
#include<string.h>

#define MaxN 1000005

char hash[2*MaxN];
int  square[101];

int main()
{
    int a,b,c,d,i,j,s,res;
    freopen("hdoj1496.txt","r",stdin);
    freopen("hdoj1496ans.txt","w",stdout);
    for (i=0;i<=100;i++) square[i]=i*i;
    while (scanf("%d%d%d%d",&a,&b,&c,&d)!=EOF)
    {
        if ((a>0 && b>0 && c>0 && d>0)
        ||  (a<0 && b<0 && c<0 && d<0))
        {
            printf("0\n");
            continue;
        }
        memset(hash,0,sizeof(hash));
        for (i=1;i<=100;i++)
            for (j=1;j<=100;j++)
            {
                s=a*square[i]+b*square[j];
                hash[s+1000000]++;
            }
        res=0;
        for (i=1;i<=100;i++)
            for (j=1;j<=100;j++)
            {
                s=c*square[i]+d*square[j];
                s=-s;
                res+=hash[s+1000000];
            }
        printf("%d\n",res<<4);
    }
    return 0;
}
