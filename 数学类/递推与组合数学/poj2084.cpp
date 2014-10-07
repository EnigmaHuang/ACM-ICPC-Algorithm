#include<stdio.h>
#include<string.h>

#define MaxSize 101

using namespace std;

class TBigInt
{
    public:
        TBigInt() {memset(data,0,sizeof(data));}
        TBigInt operator + (const TBigInt &int2)
        {
            TBigInt res;
            res.data[0]=data[0];
            if (res.data[0]<int2.data[0]) res.data[0]=int2.data[0];
            for (int i=1;i<=res.data[0];i++)
            {
                res.data[i]=res.data[i]+data[i]+int2.data[i];
                if (res.data[i]>=10)
                {
                    res.data[i+1]+=res.data[i]/10;
                    res.data[i]%=10; 
                }
            }
            if (res.data[res.data[0]+1]!=0) res.data[0]++;
            return res;
        }
        void SetValue(int n=0)
        {
            memset(data,0,sizeof(data));
            data[0]=1;
            data[1]=n;
        }
        TBigInt operator * (const TBigInt &int2)
        {
        	TBigInt res;
        	int i,j;
        	res.data[0]=data[0]+int2.data[0]-1;
        	for (i=1;i<=data[0];i++)
        	    for (j=1;j<=int2.data[0];j++)
        	        res.data[i+j-1]+=data[i]*int2.data[j];
        	for (i=1;i<=res.data[0];i++) 
        	{
        	    res.data[i+1]+=res.data[i]/10;
        	    res.data[i]%=10;
        	}
        	while (res.data[res.data[0]]>=10)
        	{
        	    res.data[res.data[0]+1]+=res.data[res.data[0]]/10; 
                    res.data[res.data[0]]%=10; 
                    res.data[0]++;  
        	}
        	return res;
        }
        void print()
        {
            for (int i=data[0];i>0;i--) printf("%d",data[i]);
        }
    private:
        int data[MaxSize];  //data[0]存的是数字长度，data[1]存个位
		            //data[2]十位，往上递推 
};

TBigInt f[105];

int main()
{
    int i,j,n;
    freopen("poj2084.txt","r",stdin);
    freopen("poj2084ans.txt","w",stdout);
    f[0].SetValue(1);
    f[1].SetValue(1);  
    f[2].SetValue(2);
    f[3].SetValue(5);   
    for (i=4;i<=100;i++)
    {
    	f[i].SetValue(0);
	for (j=0;j<i;j++) f[i]=f[i]+f[j]*f[i-j-1];
    }
    while (scanf("%d",&n) && n!=-1)
    {
        f[n].print();
        printf("\n");
    }
    return 0;
}
