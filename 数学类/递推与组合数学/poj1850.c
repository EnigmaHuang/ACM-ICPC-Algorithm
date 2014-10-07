#include<stdio.h>
#include<string.h> 

int c[27][27];

void GetCTable() //c[i][j]表示从i个数里选j个数的选择种数 
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
        for (i=1;i<len;i++) if (num[i-1]>num[i]) //检查是否升序 
	{
	    printf("0\n");
	    flag=1;
	    break;
	} 
	if (flag) continue;
        res=0;
        //计算比当前字符串长度小的字符串的数量
	//c[26][i]表示长度为i的字符串的个数  
        for (i=0;i<len;i++) res+=c[26][i];
        for (i=0;i<=len;i++) //对当前串每一位枚举其可以选择的字符 
        {
       	    //根据升序规则，当前位至少要比前一位的字符大1 
            if (i==0) ch='a'; else ch=num[i-1]+1;  
       	    //根据升序规则，当前位最多只能比这个位置实际上的字符小1 
            while (ch<=num[i]-1)
       	    {
	        res+=c['z'-ch][len-i-1]; //从'z'-ch选择len-1-i个字符的种数 
	        ch++;
       	    }
        }
        printf("%d\n",res);  
    } 
    return 0;
}
