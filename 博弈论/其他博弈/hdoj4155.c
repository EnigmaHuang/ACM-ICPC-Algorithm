#include<stdio.h>
#include<string.h>

int num[7];

int DFS(int sum)
{
    int i;
    if (sum>=31) return 0;
    for (i=1;i<=6;i++) if (num[i] && sum+i<=31)
    {
        num[i]--;
        if (DFS(sum+i)==0) 
        {
            num[i]++;
            return 1;
        }
        num[i]++;
    }
    return 0;
}

int main()
{
    int i,len,sum;
    char str[35];
    freopen("hdoj4155.txt","r",stdin);
    freopen("hdoj4155ans.txt","w",stdout);
    while (scanf("%s",str)!=EOF)
    {
        sum=0;
        len=strlen(str);
        for (i=1;i<=6;i++) num[i]=4;
        for (i=0;i<len;i++)
        {
            sum+=str[i]-'0';
            num[str[i]-'0']--;
        }
        if (sum>=31)
        {
            printf("%s ",str);
            if (len&1) printf("A\n"); else printf("B\n");
            continue;
        }
        printf("%s ",str);
        if (DFS(sum))
            if (len&1) printf("B\n"); else printf("A\n");
        else
            if (len&1) printf("A\n"); else printf("B\n");
    }
    return 0;
}
