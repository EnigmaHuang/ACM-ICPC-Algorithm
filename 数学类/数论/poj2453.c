#include<stdio.h>
#define MaxN 32 

int bin[MaxN];

int main()
{
    int num,i,j;
    freopen("poj2453.txt","r",stdin);
    freopen("poj2453ans.txt","w",stdout);
    for (i=0;i<MaxN;i++) bin[i]=1<<i;
    while (scanf("%d",&num) && num)
    {
        /*fprintf(stderr,"start at : ");
        for (i=MaxN-1;i>=0;i--) 
	    if (i>0) fprintf(stderr,"%d",(num & bin[i])>0);
	    else     fprintf(stderr,"%d\n",(num & bin[i])>0); */
        for (i=0;i<MaxN;i++)
            if ((num & bin[i]) && !(num & bin[i+1])) break;
        num=num^bin[i];
        num=num|bin[i+1];
        for (j=i-1,i=0;i<j && (num & bin[j]) && !(num & bin[i]);i++,j--)
	{
	    num=num^bin[j];
	    num=num|bin[i];
	}
	printf("%d\n",num);
	/*fprintf(stderr,"final ans: %d\n",num);
	fprintf(stderr,"end at   : ");
	for (i=MaxN-1;i>=0;i--) 
	    if (i>0) fprintf(stderr,"%d",(num & bin[i])>0);
	    else     fprintf(stderr,"%d\n\n",(num & bin[i])>0);*/
    }
    return 0;
}
