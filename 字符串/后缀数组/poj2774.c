#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 200005

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

int  num[MaxN];
char str[MaxN];

int main()
{
    int i,k,len1,len2,ans;
    freopen("poj2774.txt","r",stdin);
    freopen("poj2774ans.txt","w",stdout);
    while (scanf("%s",str)!=EOF)
    {
        len1=strlen(str);
        k=0;
        for (i=0;i<len1;i++) num[k++]=str[i]-'a'+2;
        num[k++]=1;    //相当于论文里的$
        scanf("%s",str);
        len2=strlen(str);
        for (i=0;i<len2;i++) num[k++]=str[i]-'a'+2;
        DA(num,sa,rank,k,30);
        CalcHeight(num,sa,height,k-1);
        ans=0;
        for (i=2;i<k;i++)
            if ((sa[i]<len1 && sa[i-1]>len1)
             || (sa[i]>len1 && sa[i-1]<len1))
                 ans=Max(ans,height[i]);
        printf("%d\n",ans);
    }
}
