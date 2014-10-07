#include<stdio.h>
#include<string.h>

#define Max(a,b) (a)>(b)?(a):(b)
#define MaxN 5005

struct TPos
{
    int r,c;
}hop[MaxN];

int  n,row,col;
bool map[MaxN][MaxN];

inline bool cmp(TPos &a,TPos &b)
{
    if (a.c==b.c) return a.r<b.r;
    return a.c<b.c;
}

inline bool PosInMap(int r,int c)
{
    if (r>0 && r<=row && c>0 && c<=col) return 1;
    return 0;
}

void QSort(int l,int r)
{
    int i=l,j=r;
    TPos swap,mid;
    mid=hop[(l+r)/2];
    while (i<=j)
    {
        while (cmp(hop[i],mid)) i++;
        while (cmp(mid,hop[j])) j--;
        if (i<=j)
        {
            swap=hop[i];
            hop[i]=hop[j];
            hop[j]=swap;
            i++;
            j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

int SumHop(int r,int c,int dr,int dc)
{
    int sum=0;
    while (PosInMap(r,c))
    {
        if (!map[r][c]) return 0;
        r+=dr;
        c+=dc;
        sum++;
    }
    return sum;
}

int main()
{
    int i,j,dr,dc,ans,res;

    freopen("poj1054.txt","r",stdin);
    freopen("poj1054ans.txt","w",stdout);
    
    while (scanf("%d%d",&row,&col)!=EOF)
    {
        memset(map,0,sizeof(map));

        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&hop[i].r,&hop[i].c);
            map[hop[i].r][hop[i].c]=1;
        }

        QSort(0,n-1);
        
        ans=2;
        for (i=0;i<n-1;i++)
            for (j=i+1;j<n;j++)
            {
                dr=hop[j].r-hop[i].r;
                dc=hop[j].c-hop[i].c;
                //剪枝1：因为以后的dc是增大的，如果小的dc都无法满足
                //最优解,那么后面的dc也肯定不可以，所以直接break
                if (hop[i].c+ans*dc>col) break;  
                //剪枝2：起跳位置在矩形内，不符合
                if (PosInMap(hop[i].r-dr,hop[i].c-dc)) continue;  
                //剪枝3：当前的步长可跳次数少于最优值
                if (!PosInMap(hop[i].r+ans*dr,hop[i].c+ans*dc)) continue;
                res=SumHop(hop[i].r,hop[i].c,dr,dc);
                ans=Max(ans,res);
            }
        if (ans<3) printf("0\n");
        else printf("%d\n",ans);
    }
    
    return 0;
}
