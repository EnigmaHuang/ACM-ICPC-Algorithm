#include<stdio.h>
#include<string.h>

int SG[0x1fffff+5];
int num[25],pow2[25],n;

//加入了num，现在的状态是state，返回剩余可用状态
int Add(int state,int num)
{
    int i,mul=1,ori_state=state;
    while (num*mul<=20)
    {
        state |= pow2[num*mul];
        for (i=2;i<=20;i++)
            if ((ori_state & pow2[i]) && (i+num*mul<=20))
                state |= pow2[i+num*mul];
        mul++;
    }
    return state;
}

int DFS(int state)
{
    int i,newstate;
    if (SG[state]==1) return 1;
    if (SG[state]==-1) return 0;
    for (i=2;i<=20;i++) if ((state & pow2[i])==0)
    {
        newstate=Add(state,i);
        if (DFS(newstate))
        {
            SG[state]=-1;
            return 0;
        }
    }
    SG[state]=1;
    return 1;
}

int main()
{
    int i,j,k,t=0,state,newstate,flag=0;
    freopen("poj1143.txt","r",stdin);
    freopen("poj1143ans.txt","w",stdout);
    memset(SG,0,sizeof(SG));
    pow2[0]=1;
    for (i=1;i<25;i++) pow2[i]=(1<<i);
    while (scanf("%d",&n)!=EOF && n)
    {
        state=0x1fffff;
        for (i=0;i<n;i++)
        {
            scanf("%d",&num[i]);
            state -= pow2[num[i]];
        }
        SG[0x1fffff]=1;
        flag=0;
        printf("Test Case #%d\n",++t);
        for (i=0;i<n;i++)
        {
            newstate=Add(state,num[i]);
            if (DFS(newstate))
            {
                if (flag==0)
                {
                    printf("The winning moves are:");
                    flag=1;
                }
                printf(" %d",num[i]);
            }
        }
        if (flag==0) printf("There's no winning move.");
        printf("\n\n");
    }
    return 0;
}
