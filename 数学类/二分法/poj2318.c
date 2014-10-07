#include<stdio.h>
#include<string.h>
#define MaxN 5005

struct TBox
{
    int lx1,lx2,rx1,rx2;
}box[MaxN];

int main()
{
    int n,m,i,x1,y1,x2,y2,x,y,l,r,mid,num[MaxN];
    double w,dx,dy;
    freopen("poj2318.txt","r",stdin);
    freopen("poj2318ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        scanf("%d%d%d%d%d",&m,&x1,&y1,&x2,&y2);
        box[0].lx1=box[0].lx2=x1;  //整个大箱子左右两端 
        box[n].rx1=box[n].rx2=x2;
        for (i=0;i<n;i++)
        {
            scanf("%d%d",&x1,&x2);
       	    box[i].rx1=box[i+1].lx1=x1;
       	    box[i].rx2=box[i+1].lx2=x2;
        }
        memset(num,0,sizeof(num));
        while (m--)
        {
       	    scanf("%d%d",&x,&y);
       	    l=0;r=n;
       	    while (1)
       	    {
       	        mid=(l+r)/2;
   	        dy=y1-y2;
       	        dx=box[mid].lx1-box[mid].lx2; //判断玩具是否在box[mid]的左边
       	        w=x-(y-y2)*dx/dy;
       	        if (w<box[mid].lx2)
       	        {
                    r=mid-1;
                    continue;
       	        }
       	        dx=box[mid].rx1-box[mid].rx2; //判断玩具是否在box[mid]的右边
       	        w=x-(y-y2)*dx/dy;
       	        if (w>box[mid].rx2)
       	        {
       	            l=mid+1;
       	            continue;
       	        }
       	        //fprintf(stderr,"%d: %d-%d (%d) %d-%d\n",mid,box[mid].lx1,box[mid].lx2,x,box[mid].rx1,box[mid].rx2);
       	        num[mid]++;break;             //都不是，则在box[mid]中 
       	    }
        }
        for (i=0;i<=n;i++) printf("%d: %d\n",i,num[i]); 
        printf("\n"); 
    }
    return 0;
}
