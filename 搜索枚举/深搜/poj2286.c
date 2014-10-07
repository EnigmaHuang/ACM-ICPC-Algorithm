#include<stdio.h>

int pos[8][7]={
0 ,2 ,6 ,11,15,20,22,  //方向A的数依次是第几个数
1 ,3 ,8 ,12,17,21,23,  //方向B
10,9 ,8 ,7 ,6 ,5 ,4 ,  //方向C
19,18,17,16,15,14,13,  //方向D
23,21,17,12,8 ,3 ,1 ,  //方向E，和方向B相反
22,20,15,11,6 ,2 ,0 ,  //方向F，和方向A相反
13,14,15,16,17,18,19,  //方向G，和方向D相反
4 ,5 ,6 ,7 ,8 ,9 ,10}; //方向H，和方向C相反

int aim[8]={6,7,8,11,12,15,16,17};  //目标区域的八个数依次是第几个数
int rev[8]={5,4,7,6,1,0,3,2};       //rev[i]表示第i种操作反过来是第几种操作

int map[25],ans[200],DEPTH;

int Remains()
{
    int i,cnt[4]={0,0,0,0},ans=0;
    for (i=0;i<8;++i) ++cnt[map[aim[i]]];  //算出目标区域123各自有多少个
    for (i=1;i<=3;++i) if (ans<cnt[i]) ans=cnt[i];
    return 8-ans;
}

int Move(int dir)  //按方向移动
{
    int i,head=map[pos[dir][0]];
    for (i=0;i<6;++i) map[pos[dir][i]]=map[pos[dir][i+1]];
    map[pos[dir][6]]=head;
}

int DFS(int depth)
{
    int i,cnt;
    for(i=0;i<8;++i)
    {
        Move(i);
        cnt=Remains();
        if (cnt==0)
        {
            ans[depth]=i;
            return depth+1;
        }
        if (depth+cnt<DEPTH)
        {
            ans[depth]=i;
            if (DFS(depth+1)) return depth+1;
        }
        Move(rev[i]);
    }
    return 0;
}

int main()
{
    int i;
    freopen("poj2286.txt","r",stdin);
    freopen("poj2286ans.txt","w",stdout);
    while (scanf("%d",&map[0])!=EOF && map[0])
    {
        for (i=1;i<24;++i) scanf("%d",&map[i]);
        if (Remains()==0)  //不需要移动，直接输出目标区域的数
        {
            puts("No moves needed");
            printf("%d\n",map[6]);
            continue;
        }
        for (DEPTH=1;!DFS(0);++DEPTH);  //迭代加深搜索
        for (i=0;i<DEPTH;++i) printf("%c",ans[i]+'A');
        printf("\n%d\n",map[6]);
    }
    return 0;
}
