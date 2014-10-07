#include<stdio.h>
#define MaxN 50005

int n,m,rock[MaxN];

void QSort(int l,int r)
{
    int i=l,j=r,mid,swap;
    mid=rock[(l+r)/2];
    while (i<j)
    {
        while (rock[i]<mid) i++;
        while (rock[j]>mid) j--;
        if (i<=j) 
        {
       	    swap=rock[i];
       	    rock[i]=rock[j];
       	    rock[j]=swap;
       	    i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int Check(int mid)
{
    int prev=1,cnt=0,i,dis;
    for (i=2;i<=n;i++)
    {
        dis=rock[i]-rock[prev];
        if (dis<mid) cnt++;else prev=i;
    }
    if (cnt>m) return 0; else return 1;
}

int main()
{
    int l,i,mid,r;
    freopen("poj3258.txt","r",stdin);
    freopen("poj3258ans.txt","w",stdout);
    while (scanf("%d%d%d",&l,&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&rock[i]);
        rock[++n]=0;
        rock[++n]=l;
        QSort(1,n);
        r=l;l=0;
        while (r>=l)
        {
       	    mid=(r+l)/2;
       	    //fprintf(stderr,"l=%d,r=%d,mid=%d\n",l,r,mid);
       	    if (Check(mid)) l=mid+1;else r=mid-1;
        }
        printf("%d\n",r);
        //fprintf(stderr,"ans=%d\n",r);
    }
    return 0;
}
