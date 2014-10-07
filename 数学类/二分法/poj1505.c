#include<stdio.h>
#include<string.h>
#define MaxN 505 

int m,n,ans,page[MaxN];

int solve(int mid)
{
    int i,j,sum=0,res=0;
    for (i=0;i<n;i++)
    {
        if (page[i]+sum<=mid) sum+=page[i];
        else
        {
            sum=page[i];
            res++;
        }
    }
    return res;
}

void Print()
{
    int i,j,sum,cnt=1,pre[MaxN];
    memset(pre,0,sizeof(pre)); 
    for (i=n-2,sum=page[n-1];i>=0;i--)  //从前向后先划分一次区间 
    {
        if (sum+page[i]>ans)   //因为字典序要求最小，所以前面的尽量多 
        {
            sum=page[i];
            pre[i]=1;
            cnt++;
        }
        else sum+=page[i];
    }
    for (i=0,j=cnt;j<m && i<n;i++) //从后向前补齐区间 
    {
        if(pre[i]==0)
        {
            pre[i]=1;
            j++;
        }
    }
    for (i=0;i<n-1;i++)
    {
        printf("%d ",page[i]);
        if (pre[i]) printf("/ ");
    }
    printf("%d\n",page[i]);
}

int main()
{
    int testcase,i,j,l,r,mid,res;
    freopen("poj1505.txt","r",stdin);
    freopen("poj1505ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d%d",&n,&m);
        r=l=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",&page[i]);
            r+=page[i];
            if (l<page[i]) l=page[i];
        }
        while (l<=r)
        {
            mid=(l+r)/2;
            res=solve(mid);
            //fprintf(stderr,"l=%d,r=%d,mid=%d,need men=%d\n",l,r,mid,res); 
            if (res<m)
            {
                r=mid-1;
                ans=mid;
                //fprintf(stderr,"now ans:%d\n",ans); 
            }
            else l=mid+1;
        }
        Print();
    }
    return 0;
}
