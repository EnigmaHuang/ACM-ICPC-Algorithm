#include<stdio.h>
#include<string.h>

#define N 500

int  map[N][N];
int  linkto[N];
bool visited[N];
int  n,ans;

bool find(int u) 
{  
   int i;
     
   for(i=1;i<=n;i++)  
   {  
       if( (!visited[i]) && (map[u][i]) )  
       {  
           visited[i]=true;  
           if( (linkto[i]==-1) || find(linkto[i]) )  
           {  
               linkto[i]=u;  
               return(true);  
           }  
       }  
   }  
   return(false);  
} 


int main()  
{   
    int i,j,k,src,trg;
    
    while(scanf("%d\n",&n)!=EOF)  
    {   
    	memset(map,0,sizeof(map));  
    	memset(linkto,-1,sizeof(linkto));  
    	for(i=1;i<=n;i++)  
    	{  
			scanf("%d: (%d)",&src,&k);  
        	for(j=1;j<=k;j++)  
        	{  
            	scanf("%d",&trg);   
            	map[src][trg]=1; 
        	}  
    	} 
         
        ans=0;    
        for(i=0;i<n;i++)
        {  
            memset(visited,false,sizeof(visited));  
            if (find(i)) ans++;  
        }  
        
		if (ans%2) ans+=1; 
        printf("%d\n",n-ans/2);  
    }  
    return 0;  
} 
