#include<stdio.h>

char hash[12500005*2];
int cube[101];

int main()
{
    int i,j,k,pos,ans;
    int a[5];
    freopen("poj1840.txt","r",stdin);
    freopen("poj1840ans.txt","w",stdout);
    k=0;
    for (i=-50;i<=50;i++) if (i!=0) cube[k++]=i*i*i;
    for (i=0;i<5;i++) scanf("%d",&a[i]);
    memset(hash,0,sizeof(hash));
    for (i=0;i<100;i++)
        for (j=0;j<100;j++)
        {
            pos=-(a[0]*cube[i]+a[1]*cube[j]);
            hash[pos+12500000]++;
        }
    ans=0;
    for (i=0;i<100;i++)
        for (j=0;j<100;j++)
            for (k=0;k<100;k++)
            {
                pos=a[2]*cube[i]+a[3]*cube[j]+a[4]*cube[k];
                if (pos<-12500000 || pos>12500000) continue;
                ans+=hash[pos+12500000];
            }
    printf("%d\n",ans);
    return 0;
}
