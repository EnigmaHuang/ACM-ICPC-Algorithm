/*
G++ 交 2547ms
C++ 交 1313ms
也是醉了……
*/
#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 400050

int sa[MaxN],rank[MaxN]/*,height[MaxN]*/;
int wa[MaxN],wb[MaxN],wv[MaxN],wd[MaxN];

int cmp(int *r,int a,int b,int l)
{
    return (r[a]==r[b] && r[a+l]==r[b+l]);
}

/*Doubling Algorithm倍增算法求sa和rank*/
void DA(int *r,int *sa,int *rank,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
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
    /*for (i=1;i<=n-1;i++) rank[sa[i]]=i;*/
}

/*
void CalcHeight(int *r,int *sa,int *height,int n)
{
    int i,j,k=0;
    for (i=0;i<n;i++)
    {
        if (k) k--;
        for (j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
        height[rank[i]]=k;
    }
}
*/

int num[MaxN],s[MaxN],tmp[MaxN];

struct TData
{
    int data,id;
    bool operator < (const TData & b) const
    {
        return this->data<b.data;
    }
}dat[MaxN];

void QSort(int l,int r)
{
    int i=l,j=r,mid;
    TData swap;
    mid=dat[(i+j)/2].data;
    while (i<=j)
    {
        while (dat[i].data<mid) i++;
        while (mid<dat[j].data) j--;
        if (i<=j)
        {
            swap=dat[i];
            dat[i]=dat[j];
            dat[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

void Print(int start,int end)
{
    int i;
    for (i=start;i<=end;i++) printf("%d\n",s[i]);
}

int main()
{
    int n,i,j;
    freopen("poj3581.txt","r",stdin);
    freopen("poj3581ans.txt","w",stdout);
    scanf("%d",&n);
    for (i=n-1;i>=0;i--)
    {
        scanf("%d",&s[i]);
        dat[i].data=s[i];
        dat[i].id=i;
    }
    QSort(0,n-1);
    
    tmp[0]=1;
    for (i=1;i<n;i++)
        if (dat[i].data==dat[i-1].data) tmp[i]=tmp[i-1];
        else tmp[i]=i+1;
    for (i=0;i<n;i++) num[dat[i].id]=tmp[i];
    num[n]=0;
    
    DA(num,sa,rank,n+1,n+5);
    //找第一节
    for (i=1;i<=n;i++) if (sa[i]>1) break;
    Print(sa[i],n-1);
    //剩下的部分复制一次在后面
    for (j=0;j<sa[i];j++) num[sa[i]+j]=num[j];
    n=2*sa[i];
    num[n]=0;
    DA(num,sa,rank,n+1,n+5);
    for (i=1;i<=n;i++) if (sa[i]<n/2 && sa[i]>0) break;
    Print(sa[i],n/2-1);
    Print(0,sa[i]-1);
    
    return 0;
}
