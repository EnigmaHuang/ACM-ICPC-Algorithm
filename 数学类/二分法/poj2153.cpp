#include<map>
#include<cstdio>
#include<cstring>
#include<string>

#define MaxN 10005

using namespace std;

int score[MaxN],n,m;
map<string,int> stud;

int main()
{
    int i,rank,fenshu,lm;
    char str[255];
    freopen("poj2153.txt","r",stdin);
    freopen("poj2153ans.txt","w",stdout);
    while (scanf("%d\n",&n)!=EOF)
    {
        for (i=1;i<=n;i++)
        {
       	    gets(str);
       	    stud[str]=i;
        }
        scanf("%d",&m);
        memset(score,0,sizeof(score));
        while (m--)
        {
       	    for (i=1;i<=n;i++)
       	    {
                scanf("%d ",&fenshu);
       	        gets(str);
       	        score[stud[str]]+=fenshu;
       	    }
            rank=1;
            lm=score[stud["Li Ming"]];
            for (i=1;i<=n;i++) if (score[i]>lm) rank++;
            printf("%d\n",rank);
        }
    }
    return 0;
}
