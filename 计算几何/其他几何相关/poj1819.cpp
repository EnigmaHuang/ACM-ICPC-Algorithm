#include<stdio.h>
#include<math.h>

#define MaxN 1001
#define eps  1e-8

struct Circle
{
    double x,y,r;//半径
}s[MaxN];

int main()
{
    int i,j,n,ans,p,last,k;
    int unfix[MaxN];        //是否可去(1可去，0不可去)
    int fixpos[MaxN];       //不可去的圆的位置
    double x;
    freopen("poj1819.txt","r",stdin);
    freopen("poj1819ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        p=ans=0;
        last=1;
        for (i=1;i<=n;i++)
        {
            unfix[i]=1;     //所有圆一开始都置为可去
            k=0;            //并且将前面不可去圆数置为0
            scanf("%lf",&s[i].r);
            s[i].x=s[i].y=s[i].r;  //将圆i位置初始为与y轴相切的位置
            for (j=1;j<=p;j++)
            {
                x=s[fixpos[j]].x+2*sqrt(s[i].r*s[fixpos[j]].r);//计算按fixpos[j]与i相切移动i时，i的横坐标位置
                if (x-s[i].x>eps)  //相切时的位置比现在的要靠后，那么后移圆i的位置
                {
                    s[i].x=x;      //更新横坐标位置
                    k=j;           //记录与i相切的最后一个圆的编号
                }
            }
            p=k;  //在不可去圆中清除与i相切的圆k与i之间的所有圆并将i存入不可去圆
            fixpos[++p]=i;
            if (s[i].r+s[i].x-s[last].r-s[last].x>eps) last=i;  //看看i是否最后一个不可去圆
        }
        for (i=1;i<=p;i++) unfix[fixpos[i]]=0;  //将不可去圆置为0
        for (i=last+1;i<=n;i++) unfix[i]=1;     //将last后的圆置为可去圆
        for (i=1;i<=n;i++) ans+=unfix[i];       //统计可去圆个数
        printf("%d\n",ans);
        for (i=1;i<=n;i++) if (unfix[i]) printf("%d\n",i);
    }
    return 0;
}
