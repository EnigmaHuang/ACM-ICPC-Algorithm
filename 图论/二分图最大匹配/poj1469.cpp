#include<stdio.h>
#include<string.h>

#define P 101  
#define N 301

int  map[P][N];
int  linkto[N];
bool visited[N];
int  p,n,ans;

void readdata()
{
     int i,j,stunum,stuid;
     
    memset(map,0,sizeof(map));  
    memset(linkto,-1,sizeof(linkto));  
        
    scanf("%d%d",&p,&n);  
    for(i=1;i<=p;i++)  
    {  
        scanf("%d",&stunum);  
        for(j=1;j<=stunum;j++)  
        {  
            scanf("%d",&stuid);   
            map[i][stuid]=1; 
        }  
    }      
}

bool find(int u) //u是课程，用课程匹配学生，因为学生更多 
{  
   int i;
     
   for(i=1;i<=n;i++)  
   {  
       if( (!visited[i]) && (map[u][i]) ) //标记匹配的学生  
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

void hungary()  
{  
    int i;
    
    ans=0;    
    for(i=1;i<=p;i++)
    {  
        memset(visited,false,sizeof(visited));  
        if (find(i)) ans++;  
    }  
}  

int main()  
{  
    int testcase;  
  
    scanf("%d", &testcase);  
    while(testcase--)  
    {   
        readdata();
         
        hungary();
         
        if (ans==p) printf("%s\n","YES");
        else        printf("%s\n","NO");  
    }  
    return 0;  
} 
