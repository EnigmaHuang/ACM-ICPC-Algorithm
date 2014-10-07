#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;

#define MaxN      21
#define MaxStatus 1048576+1000
#define inf       0x3f3f3f3f

struct TProgram
{
    int sec;
    char start[MaxN],end[MaxN];
}p[101];

struct TNode
{
    int sec,status;
    bool operator < (const TNode &b) const
    {
        return this->sec>b.sec;  //用时少的优先弹出
    }
};

int n,m;
int vis[MaxStatus];

int CanUseProgram(int pid,int cur_status)
{
    int i;
    for (i=0;i<n;i++) if (p[pid].start[i]!='0')
    {
        if (p[pid].start[i]=='+' &&  (cur_status&(1<<i))) return 0;
        if (p[pid].start[i]=='-' && !(cur_status&(1<<i))) return 0;
    }
    return 1;
}

int UseProgram(int pid,int cur_status)
{
    int i,res=0;
    for (i=0;i<n;i++)
    {
        if (p[pid].end[i]=='0' && (cur_status&(1<<i))) res^=(1<<i);
        if (p[pid].end[i]=='-') res^=(1<<i);
    }
    return res;
}

int BFS()
{
    int i,res=inf,new_status,final;
    priority_queue <TNode> que;
    TNode now,newsta;
    now.status=0;
    now.sec=0;
    que.push(now);
    vis[0]=1;
    final=(1<<n)-1;
    while (!que.empty())
    {
        now=que.top();
        que.pop();
        if (now.sec>res) break;
        if (now.status==final) //达到终止状态了
        {
            res=now.sec;
            return res; 
        }
        for (i=0;i<m;i++) if (CanUseProgram(i,now.status))
        {
            new_status=UseProgram(i,now.status);
            //如果没有达到过这种状态，或者新路径到这种状态的时间更少，更新之
            if (!vis[new_status] || (vis[new_status]>now.sec+p[i].sec))
            {
                newsta.status=new_status;
                newsta.sec=now.sec+p[i].sec;
                que.push(newsta);
                vis[new_status]=newsta.sec;
            }
        }
    }
    return -1;
}

int main()
{
    int i,t=0,ans;
    freopen("poj1482.txt","r",stdin);
    freopen("poj1482ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (n==0 && m==0) break;
        for (i=0;i<m;i++) scanf("%d%s%s",&p[i].sec,p[i].start,p[i].end);
        memset(vis,0,sizeof(vis));
        ans=BFS();
        printf("Product %d\n",++t);
        if (ans==-1) printf("Bugs cannot be fixed.\n\n");
        else printf("Fastest sequence takes %d seconds.\n\n",ans);
    }
    return 0;
}
