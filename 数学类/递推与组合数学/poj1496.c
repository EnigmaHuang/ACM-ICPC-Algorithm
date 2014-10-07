#include<stdio.h>
#include<string.h> 

int c[27][27];

void GetCTable()
{
    int i,j;
    for (i=0;i<=26;i++)
        for (j=0;j<=i;j++)
        {
       	    if (!j || j==i) c[i][j]=1;
       	    else c[i][j]=c[i-1][j-1]+c[i-1][j];
        }
    c[0][0]=0; 
} 

int main()
{
    int i,len,res,flag;
    char num[10],ch;
    freopen("poj1850.txt","r",stdin);
    freopen("poj1850ans.txt","w",stdout);
    GetCTable();
    while (scanf("%s",num)!=EOF)
    {
        flag=0;
        len=strlen(num);
        for (i=1;i<len;i++) if (num[i-1]>num[i])
	{
	    printf("0\n");
	    flag=1;
	    break;
	} 
	if (flag) continue;
        res=0;
        for (i=0;i<len;i++) res+=c[26][i];
        for (i=0;i<=len;i++)
        {
       	    if (i==0) ch='a'; else ch=num[i-1]+1;
       	    while (ch<=num[i]-1)
       	    {
	        res+=c['z'-ch][len-i-1];
	        ch++;
       	    }
        }
        printf("%d\n",res);
    } 
    return 0;
}
