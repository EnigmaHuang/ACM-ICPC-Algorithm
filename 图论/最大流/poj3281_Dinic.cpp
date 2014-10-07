#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define min(x,y) ((x<y)?(x):(y))

#define INF 0x7fffffff
#define MaxPoint 405 
  
int c[MaxPoint][MaxPoint];       //邻接矩阵表示剩余容量    
int dis[MaxPoint];               //距源点距离，即分层图 
     
int N,F,D,ANS;               //N为点数，M为边数
int source,target;

int BFS()   
{
    int i,j;
    queue<int> q;
    memset(dis,0xff,sizeof(dis));  //以-1填充作为未访问的标记   
    dis[source]=0;                 //源点的分层为0
    q.push(source);
    while (!q.empty())
    {
        j=q.front();
        q.pop();
        for (i=0;i<=target;i++) if (dis[i]<0 && c[j][i]>0)
        {
            dis[i]=dis[j]+1;
            q.push(i);
        }
    }
    if (dis[target]>0) return 1; else return 0; //汇点的DIS小于零,表明BFS不到汇点
}

//find代表一次增广,函数返回本次增广的流量,返回0表示无法增广   
//low是源点到现在最窄的(剩余流量最小)的边的剩余流量     
int find(int x,int low)
{
    int i,newcap=0;
    if (x==target) return low; //是汇点，直接返回
    for (i=0;i<=target;i++)  
        if (c[x][i]>0 && dis[i]==dis[x]+1 && (newcap=find(i,min(low,c[x][i]))))
		//   联通     ，是分层图的下一层  ，  能到汇点(新增流量newcap<>0)    
        {
            c[x][i]-=newcap;
            c[i][x]+=newcap;
            return newcap;
        }
    return 0;
}

void ReadData()
{
    int fi,di,f,d,i;
    scanf("%d%d%d",&N,&F,&D);
    
	for (i=1;i<=F;i++) c[0][i]+=1;
    for (i=1;i<=N;i++) c[F+i][F+N+i]+=1;
    for (i=1;i<=D;i++) c[F+2*N+i][F+2*N+D+1]+=1;
    
    for (i=1;i<=N;i++)
    {
    	scanf("%d %d",&fi,&di);
    	while (fi--)
    	{
    		scanf("%d",&f);
    		c[f][F+i]+=1;
    	}
    	while (di--)
    	{
    		scanf("%d",&d);
    		c[F+N+i][F+2*N+d]+=1;
    	}
    }
} 

int main()
{
    freopen("poj3281.txt" ,"r",stdin);
    freopen("poj3281ans.txt","w",stdout);
    
    int newcap;
    
    memset(c,0,sizeof(c));
    ReadData();
	ANS=0;
	source=0;
	target=F+2*N+D+1;
    while(BFS())//要不停地建立分层图,如果BFS不到汇点才结束
    {
	    //一次BFS要不停地找增广路,直到找不到为止
        while(newcap=find(source,INF)) ANS+=newcap;
    }    
    printf("%d\n",ANS);    
}

