#include<stdio.h>
#include<string.h>

#define MaxNode  27
#define DataType char
#define NullData 0

struct TBSTNode
{
    int left,right;
    DataType key;
}bst[MaxNode];

int num;

void Insert(DataType data)
{
    int pos=1,tmp;
    while (1)
    {
    if (data>bst[pos].key) tmp=bst[pos].right;
    if (data<bst[pos].key) tmp=bst[pos].left;
    if (tmp==0)
    {
        num++;
        bst[num].key=data;
        if (data>bst[pos].key) bst[pos].right=num;
        else bst[pos].left=num;
        break;
    }
    pos=tmp;
    }
}

void PreOrder(int t)
{
    if (bst[t].key==NullData) return;
    printf("%c",bst[t].key);
    PreOrder(bst[t].left);
    PreOrder(bst[t].right);
}

char a[26][26];

int main()
{
    int i,j,n;
    freopen("poj1577.txt","r",stdin);
    freopen("poj1577ans.txt","w",stdout);
    while(1)
    {
        n=0;
        while (scanf("%s",&a[n]),a[n][0]!='*' && a[n][0]!='$') n++;
        memset(bst,0,sizeof(bst));
        bst[1].key=a[n-1][0];
        num=1;
        for (i=n-2;i>=0;i--)
            for (j=0;a[i][j];j++) Insert(a[i][j]);
        PreOrder(1);
        printf("\n");
        if (a[n][0]=='$') break;
    }
    return 0;
}
