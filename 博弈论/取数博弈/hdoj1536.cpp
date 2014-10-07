#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

/*
  博弈论SG函数模板，要求调用前SG初始化为-1，但不需要每求一次就初始化一次
  k为状态转移集合S的大小，S[i]表示状态转移集合数组
*/
#define MaxN    10001
#define MaxRule 101

int SG[MaxN],*S,k;

void InitSG(int rulenum,int *rules)  //rules从0开始存
{
    k=rulenum;
    memset(SG,-1,sizeof(SG));
    sort(rules,rules+k);  //S需要从小到大排序
    S=rules;
}

int SpragueGrundy(int x)
{
    int i,res;
    bool vis[MaxRule+2];  //哪怕所有的状态都可转移，其SG值都不一样，最多填充前1～转移数
    if (SG[x]!=-1) return SG[x];
    memset(vis,0,sizeof(vis));
    for (i=0;i<k;i++) if (x>=S[i])
    {
        SpragueGrundy(x-S[i]);
        vis[SG[x-S[i]]]=1;
    }
    for (i=0;i<MaxN;i++) if (!vis[i])
    {
        res=i;
        break;
    }
    SG[x]=res;
    return res;
}

/*----------SG Template Over----------*/

int s[MaxRule];

int main()
{
    int i,cases,t,k,sum,num;
    freopen("hdoj1536.txt","r",stdin);
    freopen("hdoj1536ans.txt","w",stdout);
    while (scanf("%d",&k)!=EOF && k)
    {
        for (i=0;i<k;i++) scanf("%d",&s[i]);
        InitSG(k,s);
        scanf("%d",&cases);
        while (cases--)
        {
            sum=0;
            scanf("%d",&t);
            while (t--)
            {
                scanf("%d",&num);
                sum^=SpragueGrundy(num);
            }
            if (sum==0) printf("L"); else printf("W");
        }
        printf("\n");
    }
    return 0;
}
