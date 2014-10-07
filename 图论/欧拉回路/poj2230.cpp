#include<iostream>
#include<cstdio>

using namespace std;

const int MaxNode=10000;

struct Edge
{
    int trg,next;
    bool vis;
}e[MaxNode*10];
int head[MaxNode];
int edgenum;

void addedge(int u,int v)
{
    e[edgenum].trg=v;
    e[edgenum].next=head[u];
    e[edgenum].vis=false;
    head[u]=edgenum++;                                              
}

void euler(int u)
{
     int i;
     for(i=head[u];i;i=e[i].next)
     {
        if(!e[i].vis)
        {
            e[i].vis=true;   
            euler(e[i].trg);
        }
     }
     printf("%d\n",u);
}

int main()
{
    int n,m,u,v;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(head,0,sizeof(head)); 
        edgenum=1;    
        while(m--)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        euler(1);
    }
    return 0;
}