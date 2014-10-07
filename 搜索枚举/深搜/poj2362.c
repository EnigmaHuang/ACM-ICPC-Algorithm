#include<stdio.h>
#include<string.h>
#define MaxN 21

int len[MaxN],used[MaxN];
int solved,sticknum,totallen,sidelen;

void QSort(int l,int r)
{
    int i,j,mid,swap;
    i=l;j=r;
    mid=len[(l+r)/2];
    while (i<=j)
    {
        while (len[i]>mid) i++;
        while (len[j]<mid) j--;
        if (i<=j)
        {
            swap=len[i];
            len[i]=len[j];
            len[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

void DFS(int startpos,int sumlen,int searched)
{
    int i,j;
    if (searched==3)
    {
        solved=1;
        return;
    }
    if (sumlen==sidelen) DFS(1,0,searched+1);
    if (solved) return;  //搜索树下端已经搜出了结果，直接返回 
    for (i=startpos;i<=sticknum;i++)
    {
        if (!used[i] && sumlen+len[i]<=sidelen)
        {
            used[i]=1;
            DFS(i+1,sumlen+len[i],searched);
            if (solved) return;
            else //剪枝4：相同长度的已经搜索过了，并且不行，就跳过 
            {
                used[i]=0;
                while (len[i]==len[i+1]) i++;
            }
            
        } 
    }
} 

int main()
{
    int testcase,i;
    freopen("poj2362.txt","r",stdin);
    freopen("poj2362ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d",&sticknum);
        solved=totallen=0;
        for (i=1;i<=sticknum;i++) 
        {
            scanf("%d",&len[i]);
            totallen+=len[i];
        }
        if (totallen%4!=0) printf("no\n"); //剪枝1：总长度要是4的倍数 
        else 
        {
            QSort(1,sticknum); //剪枝3：排序，从大到小搜索 
            memset(used,0,sizeof(used));
            sidelen=totallen/4;
            if (len[1]>sidelen) //剪枝2：最长枝条要小于边长 
            {
                printf("no\n");
                continue;
            }
            DFS(1,0,0);
            if (solved) printf("yes\n"); else printf("no\n"); 
        }
    }
}
