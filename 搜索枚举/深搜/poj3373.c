#include<stdio.h>
#include<string.h>

#define MaxN 101
#define MaxL 10001

int len,k,n[MaxN],ans[MaxN];
int flag[MaxN][MaxL],mod[MaxN][10];

char num[MaxN];

/*mod[i][j]表示j*(10^i) mod k，使用模同余方式得到*/
void InitMod()
{
    int i,j;
    for (i=0;i<=9;i++) mod[0][i]=i%k;
    for (i=1;i<len;i++)
        for (j=0;j<=9;j++) mod[i][j]=(mod[i-1][j]*10)%k;
}

/*pos表示现在搜索的位置是n中的哪一位
  restnum表示还能更改多少个数字
  mod_k表示当前数字串mod k的结果*/
int DFS(int pos,int restnum,int mod_k)
{
    int i,j,new_mod_k;
    if (mod_k==0) return 1;
    if (restnum==0 || pos<0) return 0;
    //非常重要的剪枝，不加会超时：如果当前参数的改变长度
    //小于曾经在这个位置得到这个余数的的改变长度，不是最优解，返回
    if (restnum<=flag[pos][mod_k]) return 0;  
    
    for (i=pos;i>=0;i--)  //搜索当前参数下比n小的数，从高位开始搜
        for (j=0;j<n[i];j++)
        {
            if (i==len-1 && j==0) continue;
            new_mod_k=(mod_k-(mod[i][n[i]]-mod[i][j])+k)%k;
            ans[i]=j;
            if (DFS(i-1,restnum-1,new_mod_k)) return 1;
            ans[i]=n[i];
        }

    for (i=0;i<=pos;i++)  //搜索当前参数下比n大的数，从低位开始搜
        for (j=n[i]+1;j<10;j++)
        {
            new_mod_k=(mod_k-(mod[i][n[i]]-mod[i][j])+k)%k;
            ans[i]=j;
            if (DFS(i-1,restnum-1,new_mod_k)) return 1;
            ans[i]=n[i];
        }
        
    flag[pos][mod_k]=restnum;  //搜索失败，更新剪枝信息
    return 0;
}

int main()
{
    int i,n_mod_k;
    freopen("poj3373.txt","r",stdin);
    freopen("poj3373ans.txt","w",stdout);
    while (scanf("%s%d",num,&k)!=EOF)
    {
        n_mod_k=0;
        len=strlen(num);
        InitMod();
        for (i=0;i<len;i++)
        {
            n[i]=num[len-i-1]-'0';                   //倒过来存放n，方便使用
            ans[i]=n[i];
            n_mod_k=(n_mod_k+mod[i][n[i]])%k;        //模同余计算n mod k
        }
        memset(flag,0,sizeof(flag));
        for (i=1;i<=len;i++) if (DFS(len-1,i,n_mod_k)) break;
        for (i=len-1;i>=0;i--) printf("%d",ans[i]);  //可以修改的位数从小到大枚举
        printf("\n");
    }
    return 0;
}
