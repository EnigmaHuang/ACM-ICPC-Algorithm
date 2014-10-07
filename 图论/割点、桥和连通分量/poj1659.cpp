#include<cstdio>
#include<cstring>

using namespace std;

const int MaxN = 11;

struct TData
{
    int id,degree;
};

int map[MaxN][MaxN];
int t,n,hasans;
struct TData p[MaxN];

void QSort(int l,int r)
{
    int i=l,j=r,mid=p[(l+r)/2].degree;
    struct TData swap;
    while (i<=j)
    {
        while (p[i].degree>mid) i++;
        while (p[j].degree<mid) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (j>l) QSort(l,j);
}

int Check()
{
	int i;
	for (i=2;i<=1+p[1].degree;i++)
	{
		p[i].degree--;
		map[p[1].id][p[i].id]=1;
		map[p[i].id][p[1].id]=1;
		if (p[i].degree<0) return 0;
	}
	p[1].degree=0;
	return 1;
}

int main()
{
    int i,j;
    freopen("poj1659.txt","r",stdin);
    freopen("poj1659ans.txt","w",stdout);
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (i=1;i<=n;i++) 
    	{
            p[i].id=i;
            scanf("%d",&p[i].degree);
    	}
        QSort(1,n);
        hasans=1;
        memset(map,0,sizeof(map));
        while (p[1].degree>0)
        {
	    if (!Check())
	    {
                hasans=0;
                break;
            }     	
            QSort(1,n);	
        }
        if (hasans)
        {
            printf("YES\n");
            for (i=1;i<=n;i++)
            {
                for (j=1;j<=n;j++) printf("%d ",map[i][j]);
                printf("\n");
            }
            printf("\n");
        }
        else printf("NO\n\n");
    }
}
