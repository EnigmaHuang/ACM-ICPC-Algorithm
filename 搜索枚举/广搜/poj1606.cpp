#include<stdio.h>
#include<string.h>

#define MaxN 1005
#define Min(a,b) (a)<(b)?(a):(b)

struct TNode
{
    int opt;  //操作编号
    int a,b;  //水的数量
    int pre;  //上一个状态
}q[MaxN*MaxN];

bool vis[MaxN][MaxN];
char str[6][10]={"fill A" ,"fill B"  ,"empty A",
                 "empty B","pour A B","pour B A"};
//各操作对应输出的字符串

void Print(int pos)
{
    if (q[pos].pre!=-1)
    {
        Print(q[pos].pre);
        printf("%s\n",str[q[pos].opt]);
    }
}

void BFS(int a,int b,int c)
{
    int steps=0;
    int head=0,tail=1;
    int cnt,pos,wat1,wat2;
    q[0].a=q[0].b=0;
    q[0].pre=-1;
    while (tail>head)
    {
        cnt=tail-head;
        while (cnt--)
        {
            pos=head;
            if (q[pos].b==c)
            {
                Print(pos);
                printf("success\n");
                return;
            }
            if (!vis[a][q[pos].b])
            {
                q[tail].opt=0;
                q[tail].a=a;
                q[tail].b=q[pos].b;
                q[tail].pre=head;
                vis[a][q[pos].b]=1;
                tail++;
            }
            if (!vis[q[pos].a][b])
            {
                q[tail].opt=1;
                q[tail].a=q[pos].a;
                q[tail].b=b;
                q[tail].pre=head;
                vis[q[pos].a][b]=1;
                tail++;
            }
            if (!vis[0][q[pos].b])
            {
                q[tail].opt=2;
                q[tail].a=0;
                q[tail].b=q[pos].b;
                q[tail].pre=head;
                vis[0][q[pos].b]=1;
                tail++;
            }
           if (!vis[q[pos].a][0])
           {
                q[tail].opt=3;
                q[tail].a=q[pos].a;
                q[tail].b=0;
                q[tail].pre=head;
                vis[q[pos].a][0]=1;
                tail++;
            }
            wat1=Min(q[pos].a,b-q[pos].b);
            if (!vis[q[pos].a-wat1][q[pos].b+wat1])
            {
                q[tail].opt=4;
                q[tail].a=q[pos].a-wat1;
                q[tail].b=q[pos].b+wat1;
                q[tail].pre=head;
                vis[q[pos].a-wat1][q[pos].b+wat1]=1;
                tail++;
            }
            wat2=Min(a-q[pos].a,q[pos].b);
            if (!vis[q[pos].a+wat2][q[pos].b-wat2])
            {
                q[tail].opt=5;
                q[tail].a=q[pos].a+wat2;
                q[tail].b=q[pos].b-wat2;
                q[tail].pre=head;
                vis[q[pos].a+wat2][q[pos].b-wat2]=1;
                tail++;
            }
            head++;
        }
        steps++;
    }
}

int main()
{
    int a,b,n;
    freopen("poj1606.txt","r",stdin);
    freopen("poj1606ans.txt","w",stdout);
    while (scanf("%d%d%d",&a,&b,&n)!=EOF)
    {
        memset(vis,0,sizeof(vis));
        vis[0][0]=1;
        BFS(a,b,n);
    }
    return 0;
}
