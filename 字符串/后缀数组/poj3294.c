#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)
#define MaxN 100500

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
    for (i=1;i<=n-1;i++) rank[sa[i]]=i;
}

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

#define MaxL 1005
#define nMax 105

int  sum[nMax];
char s[nMax][MaxL];
int  num[MaxN],n,m;
int  vis[nMax];

int GetStrIDByLen(int len)
{
    int l=0,r=n-1,mid;
    while (l<r)
    {
        mid=(l+r)/2;
        if (sum[mid]<len) l=mid+1;
        else r=mid;
    }
    return l;
}

int Check(int len,int outputans)
{
    int i,j,k,id,cnt;
    i=n+1;
    while (1)
    {
        while (i<=m && height[i]<len) i++;
        if (i>m) break;
        memset(vis,0,sizeof(vis));
        id=GetStrIDByLen(sa[i-1]);
        vis[id]=1;
        cnt=1;
        while (i<=m && height[i]>=len)
        {
            id=GetStrIDByLen(sa[i]);
            if (!vis[id])
            {
                vis[id]=1;
                cnt++;
            }
            i++;
        }
        if (2*cnt>n)
        {
            if (!outputans) return 1;
            else
            {
                k=sa[i-1];
                for (j=0;j<len;j++) printf("%c",num[k++]+'a'-100);
                printf("\n");
            }
        }
    }
    return 0;
}

int main()
{
    int i,j,k,len,maxlen;
    int l,r,mid;
    freopen("poj3294.txt","r",stdin);
    freopen("poj3294ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        scanf("%s",s[0]);
        sum[0]=strlen(s[0]);
        maxlen=sum[0];
        if (n==1)
        {
            printf("%s\n\n",s[0]);
            continue;
        }
        for (i=1;i<n;i++)
        {
            scanf("%s",s[i]);
            sum[i]=sum[i-1]+strlen(s[i])+1;
        }
        k=0;
        for (i=0;i<n;i++)
        {
            len=strlen(s[i]);
            for (j=0;j<len;j++) num[k++]=s[i][j]-'a'+100;
            num[k++]=i;
        }

        m=k-1;
        DA(num,sa,rank,k,130);
        CalcHeight(num,sa,height,k-1);

        l=0;
        r=m;
        while (l<r)
        {
            mid=(l+r+1)/2;
            if (Check(mid,0)) l=mid;
            else r=mid-1;
        }

        if (l==0) printf("?\n\n");
        else
        {
            Check(l,1);
            printf("\n");
        }
    }
    return 0;
}
