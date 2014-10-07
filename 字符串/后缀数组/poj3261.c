#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 20005

int sa[MaxN],rank[MaxN],height[MaxN];
int wa[MaxN],wb[MaxN],wv[MaxN],wd[MaxN];

int cmp(int *r,int a,int b,int l)
{
    return (r[a]==r[b] && r[a+l]==r[b+l]);
}

/*Doubling Algorithm倍增算法求sa和rank*/
void DA(int *r,int *sa,int *rank,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    //第一轮，子串长度为1
    for (i=0;i<m;i++) wd[i]=0;

    for (i=0;i<n;i++)
    {
        x[i]=r[i];
        wd[r[i]]++;
    }

    for (i=1;i<m;i++) wd[i]+=wd[i-1];
    for (i=n-1;i>=0;i--)
    {
        wd[x[i]]--;
        sa[wd[x[i]]]=i;
    }
    //第2~k轮，满足2^k<=n
    for (j=1,p=1;p<n;j*=2,m=p)
    {
        for (p=0,i=n-j;i<n;i++) y[p++]=i;
        for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;
        for (i=0;i<n;i++) wv[i]=x[y[i]];
        for (i=0;i<m;i++) wd[i]=0;
        for (i=0;i<n;i++) wd[wv[i]]++;
        for (i=1;i<m;i++) wd[i]+=wd[i-1];
        for (i=n-1;i>=0;i--)
        {
            wd[wv[i]]--;
            sa[wd[wv[i]]]=y[i];
        }
        t=x;
        x=y;
        y=t;
        x[sa[0]]=0;
        p=1;
        for (i=1;i<n;i++)
        {
            if (cmp(y,sa[i-1],sa[i],j)) x[sa[i]]=p-1;
            else x[sa[i]]=p++;
        }
    }
    for (i=1;i<=n-1;i++) rank[sa[i]]=i;
}

void CalcHeight(int *r,int *sa,int *height,int n)
{
    int i,j,k=0;
    for (i=0;i<n;height[rank[i++]]=k)
    {
        if (k) k--;
        for (j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    }
}

int n,k,ans,num[MaxN];

int Check(int len)
{
    int i=2,cnt;
    while (1)
    {
	while (i<=n && height[i]<len) i++;
	if (i>n) break;  
	cnt=1;
	while (i<=n && height[i]>=len)
	{
	    cnt++;
	    i++;
	}
	if (cnt>=k) return 1;  //存在一个分组满足要求即可
    }
    return 0;
}

void BinSearch(int startl,int startr)
{
    int l=startl,r=startr,mid;
    while (l<r)
    {
	mid=(l+r+1)/2;
	if (Check(mid)) l=mid; else r=mid-1;
    }
    ans=l;
}

int main()
{
    int i;
    freopen("poj3261.txt","r",stdin);
    freopen("poj3261ans.txt","w",stdout);
    while (scanf("%d%d",&n,&k)!=EOF)
    {
        for (i=0;i<n;i++) scanf("%d",&num[i]);
        num[n]=0;
        DA(num,sa,rank,n+1,10000);
        CalcHeight(num,sa,height,n);
        BinSearch(1,n);
        printf("%d\n",ans);
    }
}
