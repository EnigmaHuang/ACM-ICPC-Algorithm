#include<stdio.h>
#include<string.h>

#define MaxN 1000005
#define MaxM 90005

int  H[MaxN],HPri[MaxM],HSemiPri[MaxN],cnt;

void GetHNum()
{
    int i;
    for (i=1;i<MaxN;i+=4) H[i]=1; 
}

void GetHPrimeNum()
{
    int i,j;
    for (i=5;i*i<MaxN;i+=4) if (H[i])
    	for (j=5;i*j<MaxN;j+=4) H[i*j]=0;  //往上筛 
    cnt=0;
    for (i=5;i<MaxN;i+=4) if (H[i]) HPri[cnt++]=i; 
}

void GetHSemiPrimeNum()
{
    int i,j,w;
    memset(H,0,sizeof(H));
    for (i=0;HPri[i]*HPri[i]<MaxN;i++)  //注意范围限制 
        for (j=i;j<cnt;j++)
	{
	    w=HPri[i]*HPri[j];
	    if (w>=MaxN) break;
	    if ((w-1)%4==0) H[w]=1; 
	}
    for (i=1;i<=MaxN;i++)
    {
        HSemiPri[i]=HSemiPri[i-1];
	if (H[i]) HSemiPri[i]++; 
    } 
}

int main()
{
    int num;
    freopen("poj3292.txt","r",stdin);
    freopen("poj3292ans.txt","w",stdout);
    GetHNum();
    GetHPrimeNum();
    GetHSemiPrimeNum();
    while (scanf("%d",&num)!=EOF && num) printf("%d %d\n",num,HSemiPri[num]);
    return 0;
} 
