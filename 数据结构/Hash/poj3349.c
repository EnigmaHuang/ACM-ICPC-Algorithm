#include<stdio.h>
#include<string.h>

#define prime 14997

struct Node
{
    int arm[6];
}hash[prime][100];

int num[prime];

int cmp(struct Node a,struct Node b)
{
    int i,j;
    for (i=0;i<6;i++)
        if (a.arm[0]==b.arm[i])
        {
            for (j=1;j<6;j++) if (a.arm[j]  !=b.arm[(i+j)%6]) break;
            if (j==6) return 1;
            for (j=1;j<6;j++) if (a.arm[6-j]!=b.arm[(i+j)%6]) break;
            if (j==6) return 1;
        }
    return 0;
}

int Check(int k,struct Node src)
{
    int i,j;
    for (i=0;i<num[k];i++)
        if (cmp(hash[k][i],src)) return 1;
    return 0;
}

int main()
{
    int n,i,j,sum,pos,flag;
    struct Node cur;
    freopen("poj3349.txt","r",stdin);
    freopen("poj3349ans.txt","w",stdout);
    /*while (scanf("%d",&n)!=EOF) 狗日的，这句加了就错了*/
    {
        flag=0;
        for (i=0;i<n;i++)
        {
            sum=0;
            for (j=0;j<6;j++)
            {
                scanf("%d",&cur.arm[j]);
                sum+=cur.arm[j];
            }
            pos=sum%prime;
            if (Check(pos,cur))
            {
                flag=1;
                break;
            }
            hash[pos][num[pos]]=cur;
            num[pos]++;
        }
        if (flag) printf("Twin snowflakes found.\n");
        else printf("No two snowflakes are alike.\n");
    }
    return 0;
}
