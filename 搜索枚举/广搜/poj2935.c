#include<stdio.h>
#include<string.h>

#define MaxN 7

struct TNode
{
    int r,c,pre;
    char opt;
}end,que[MaxN*MaxN];

int map[2*MaxN][2*MaxN];
int dr[4]={-2,0,0,2};
int dc[4]={0,-2,2,0};

int sr,sc;

char Walk(int dir)
{
    if (dir==0) return 'N';
    if (dir==1) return 'W';
    if (dir==2) return 'E';
    if (dir==3) return 'S';
}

int InMap(int r,int c)
{
    if (r>=2 && r<=12 && c>=2 && c<=12) return 1;
    return 0;
}

int HasWall(int r,int c,int dir)
{
    if (dir==0) return map[r+1][c];
    if (dir==1) return map[r][c+1];
    if (dir==2) return map[r][c-1];
    if (dir==3) return map[r-1][c];
}

void Output(int k)
{          
    if (k==0) return;
    else
    {
        Output(que[k].pre);
        printf("%c",que[k].opt);
    }
}

void BFS()
{
    int head=0,tail=1,flag=0,i;
    int nowr,nowc,newr,newc,ans;
    
    que[0].r=2*sr;
    que[0].c=2*sc;
    que[0].pre=0;
    while (tail>head)
    {
        nowr=que[head].r;
        nowc=que[head].c;
        for (i=0;i<4;i++)
        {
            newr=nowr+dr[i];
            newc=nowc+dc[i];
            if (InMap(newr,newc) && !map[newr][newc] && !HasWall(newr,newc,i))
            {
                map[newr][newc]=1;
                que[tail].r=newr;
                que[tail].c=newc;
                que[tail].pre=head;
                que[tail].opt=Walk(i);
                if (newr==end.r && newc==end.c)
                {
                    flag=1;
                    ans=tail;
                    break;
                }
                tail++;
            }
        }
        head++;
        if (flag) break;
    }
    Output(ans);
    printf("\n");
}

int main()
{
    int r,c,rr,cc,tmp,i,j;
    
    freopen("poj2935.txt","r",stdin);
    freopen("poj2935ans.txt","w",stdout);

    while (scanf("%d%d",&c,&r)!=EOF)
    {
        if (r==0 && c==0) break;
        memset(map,0,sizeof(map));
        sr=r;
        sc=c;
        map[2*r][2*c]=1;
        scanf("%d%d",&c,&r);
        end.r=2*r;
        end.c=2*c;
        for (i=0;i<3;i++) //¹¹ÔìÇ½
        {   
            scanf("%d%d%d%d",&c,&r,&cc,&rr);
            if (r==rr) for (j=c;j<cc;j++) map[2*r+1][2*j+2]=1;
            else       for (j=r;j<rr;j++) map[2*j+2][2*c+1]=1;
        }
        BFS();
    }
    return 0;
}
