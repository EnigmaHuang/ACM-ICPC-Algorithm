#include<stdio.h>
#include<string.h>

char key[26];
char str[80];

int main()
{
    int i,len;
    freopen("poj2141.txt","r",stdin);
    freopen("poj2141ans.txt","w",stdout);
    while (scanf("%s",key)!=EOF)
    {
        getchar();
        gets(str);
        len=strlen(str);
        for (i=0;i<len;i++)
        {
            if (str[i]>='a' && str[i]<='z')
                str[i]=key[str[i]-'a'];
            if (str[i]>='A' && str[i]<='Z')
                str[i]=key[str[i]-'A']-'a'+'A';
        }
        puts(str);
    }
    return 0;
}
