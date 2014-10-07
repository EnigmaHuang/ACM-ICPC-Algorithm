#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>

#define CharsetBase 'a'
#define CharsetSize 28

using namespace std;

struct TrieNode        //动态建树
{
    TrieNode* next[CharsetSize];     //26个小写字母加上'?'、'*'
    vector<int> pattern;    //标记该节点所代表的字符串是哪些模式串
    TrieNode(){memset(next,NULL,sizeof(next));}
};

TrieNode *root=new TrieNode();

void Insert(char str[],int pos)
{
    TrieNode *p=root;
    int i,j;
    for (i=0;str[i];i++)
    {
        if (str[i]=='?') j=26;
        else if (str[i]=='*') j=27;
        else j=str[i]-CharsetBase;
        if (p->next[j]==NULL) p->next[j]=new TrieNode();
        p=p->next[j];
    }
    p->pattern.push_back(pos);
}

vector<int> ans;

void DFS(char str[],int k,TrieNode *p)    //当前位置是在节点p,要查找的字符str[k]
{
    int i,s;
    TrieNode *q;
    if (str[k]=='\0')    //字符串结尾
    {
        while (p!=NULL)
        {
            s=p->pattern.size();
            for (i=0;i<s;++i) ans.push_back(p->pattern[i]);  //把所有匹配的模式串保存起来
            p=p->next[27];        //因为*通配符可以当作0个字符，继续往下走
        }
    }
    else
    {
        q=p->next[str[k]-CharsetBase];
        if (q!=NULL) DFS(str,k+1,q);
        q=p->next[26];    //模式串当前位置上的字符是?
        if (q!=NULL) DFS(str,k+1,q);
        q=p->next[27];    //模式串当前位置上的字符是*
        if (q!=NULL) for (;k<=strlen(str);k++) DFS(str,k,q); // *通配符可以匹配任意个字符
    }
}

int main()
{
    int n,m,i,s;
    char str[25];
    freopen("poj1816.txt","r",stdin);
    freopen("poj1816ans.txt","w",stdout);
    scanf("%d %d", &n, &m);
    for (i=0;i<n;++i)
    {
        scanf("%s",str);
        Insert(str,i);
    }
    while (m--)
    {
        scanf("%s",str);
        ans.clear();
        DFS(str,0,root);    //从根结点开始搜索
        if (ans.empty()) printf("Not match\n");
        else
        {
            //vector储存的结果排序后再去重
            sort(ans.begin(),ans.end());
            printf("%d ",ans[0]);
            s=ans.size();
            for (i=1;i<s;++i) if (ans[i]!=ans[i-1]) printf("%d ",ans[i]);
            printf("\n");
        }
    }
    return 0;
}
