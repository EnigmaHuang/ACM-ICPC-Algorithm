/*
在程序实现的时候，我们只是用一个cap数组来记录容量，而不记录流量。
当流量+1的时候，我们可以通过容量-1来实现，以方便程序的实现。
正向用cap[u][v],则反向用cap[v][u]表示。

328K，16MS
*/

#include<iostream>
#include<queue>

using namespace std;

const int N=201;  
const int INF=0x7fffffff;
int n,m,sum,s,t,w;           //s,t为始点和终点
int cap[N][N],a[N],p[N];

int min(int a,int b) {return a<=b?a:b;}

void Edmonds_Karp() 
{
    int i,u,v;
    queue<int> q;  //队列，用bfs找增广路
    while(1) 
    {
        memset(a,0,sizeof(a));//每找一次，初始化一次
        a[s]=INF;
        q.push(s);//源点入队    
        while(!q.empty())
        {
            u=q.front();
            q.pop();
            for(v=1;v<=m;v++)
            {
                if(!a[v]&&cap[u][v]>0)
                {
	            p[v]=u;
	            q.push(v);
	            a[v]=min(a[u],cap[u][v]);//s-v路径上的最小残量
	            }
	        }
	    }
		
	    if(a[m]==0) break; //找不到增广路,则当前流已经是最大流
	     
	    sum+=a[m];//流加上
	    for(i=m;i!=s;i=p[i]) //从汇点顺着这条增广路往回走
	    {
	        cap[p[i]][i]-=a[m];//更新正向流量
	        cap[i][p[i]]+=a[m];//更新反向流量
	    }
    }
}

int main() 
{  
    //freopen("poj1273.txt","r",stdin);
	//freopen("poj1273ans.txt","w",stdout);
    int v,u;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
	s=1;//从1开始
	t=m;//m为汇点
	sum=0;//记录最大流量
	memset(cap,0,sizeof(cap));//初始化
	while(n--)
	{
	    scanf("%d%d%d",&u,&v,&w);
	    cap[u][v]+=w;//注意图中可能出现相同的边
        }
	Edmonds_Karp();
	printf("%d\n",sum);
    }
    return 0;
}