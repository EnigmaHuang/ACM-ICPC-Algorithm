#include<stdio.h>

int n,num[14],select[6]; 

void DFS(int depth,int pos)
{
    int i;
    if (pos>n || depth+n-pos<=0) return;   //剪枝，dep+n-pos>0则num[]还有足够的数存到select[]中
    if (depth==6)  //选完了，输出
    {  
        for (i=0;i<6;i++) printf("%d ",select[i]);
        printf("\n");
        return;
    }
    select[depth]=num[pos];
    DFS(depth+1,pos+1);  //选了num[p]，下一个
    DFS(depth  ,pos+1);  //没选num[p]
}

int main()
{
    int i;
    freopen("poj2245.txt","r",stdin);
    freopen("poj2245ans.txt","w",stdout);
    
    while (scanf("%d",&n)!=EOF && n!=0)
    {
        for (i=0;i<n;i++) scanf("%d",&num[i]);
        DFS(0,0);
        printf("\n");
    }
    return 0;
}
