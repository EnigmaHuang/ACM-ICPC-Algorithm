#include <stdio.h>
#include <string.h>
#define MaxN 100005 

int L,n,m,pos[MaxN];

int Check(int mid)
{
    int i,cnt=1,cur=1;
    for (i=1;i<=n;i++)
    {
        while (i<=n && pos[i]-pos[cur]<mid) i++;
        cur=i;cnt++;
        if (i<=n && cnt==m) return 1;
    }
    return 0;
}

void QSort(int l,int r)
{
    int i=l,j=r,mid,swap;
    mid=pos[(l+r)/2];
    while (i<=j)
    {
        while (pos[i]<mid) i++;
        while (pos[j]>mid) j--;
        if (i<=j)
        {
       	    swap=pos[i];
       	    pos[i]=pos[j];
       	    pos[j]=swap;
       	    i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int main()
{
    int i,l,r,mid,ans;
    freopen("poj2456.txt","r",stdin);
    freopen("poj2456ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&pos[i]);
        QSort(1,n);
        l=0;
	r=pos[n]-pos[1]+1;   
        while (l<r)
        {
            mid=(l+r)/2;
            fprintf(stderr,"l=%d,r=%d,mid=%d\n",l,r,mid); 
            if (Check(mid)) 
            {
                ans=mid;
                l=mid+1;
                fprintf(stderr,"now ans : %d\n",ans); 
            }
            else r=mid;
        }
        printf("%d\n",ans);
    }
    return 0;
}

